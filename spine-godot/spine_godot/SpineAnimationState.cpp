/******************************************************************************
 * Spine Runtimes License Agreement
 * Last updated July 28, 2023. Replaces all prior versions.
 *
 * Copyright (c) 2013-2023, Esoteric Software LLC
 *
 * Integration of the Spine Runtimes into software or otherwise creating
 * derivative works of the Spine Runtimes is permitted under the terms and
 * conditions of Section 2 of the Spine Editor License Agreement:
 * http://esotericsoftware.com/spine-editor-license
 *
 * Otherwise, it is permitted to integrate the Spine Runtimes into software or
 * otherwise create derivative works of the Spine Runtimes (collectively,
 * "Products"), provided that each user of the Products must obtain their own
 * Spine Editor license and redistribution of the Products in any form must
 * include this license and copyright notice.
 *
 * THE SPINE RUNTIMES ARE PROVIDED BY ESOTERIC SOFTWARE LLC "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ESOTERIC SOFTWARE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES,
 * BUSINESS INTERRUPTION, OR LOSS OF USE, DATA, OR PROFITS) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THE
 * SPINE RUNTIMES, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include "SpineAnimationState.h"
#include "SpineTrackEntry.h"
#include "SpineEvent.h"

void SpineAnimationState::_bind_methods() {
	ClassDB::bind_method(D_METHOD("update", "delta"), &SpineAnimationState::update, DEFVAL(0));
	ClassDB::bind_method(D_METHOD("apply", "skeleton"), &SpineAnimationState::apply);
	ClassDB::bind_method(D_METHOD("clear_tracks"), &SpineAnimationState::clear_tracks);
	ClassDB::bind_method(D_METHOD("clear_track"), &SpineAnimationState::clear_track);
	ClassDB::bind_method(D_METHOD("get_num_tracks"), &SpineAnimationState::get_num_tracks);
	ClassDB::bind_method(D_METHOD("set_animation", "animation_name", "loop", "track_id"), &SpineAnimationState::set_animation, DEFVAL(true), DEFVAL(0));
	ClassDB::bind_method(D_METHOD("add_animation", "animation_name", "delay", "loop", "track_id"), &SpineAnimationState::add_animation, DEFVAL(0), DEFVAL(true), DEFVAL(0));
	ClassDB::bind_method(D_METHOD("set_empty_animation", "track_id", "mix_duration"), &SpineAnimationState::set_empty_animation);
	ClassDB::bind_method(D_METHOD("add_empty_animation", "track_id", "mix_duration", "delay"), &SpineAnimationState::add_empty_animation);
	ClassDB::bind_method(D_METHOD("set_empty_animations", "mix_duration"), &SpineAnimationState::set_empty_animations);
	ClassDB::bind_method(D_METHOD("get_current", "track_id"), &SpineAnimationState::get_current);
	ClassDB::bind_method(D_METHOD("get_time_scale"), &SpineAnimationState::get_time_scale);
	ClassDB::bind_method(D_METHOD("set_time_scale", "time_scale"), &SpineAnimationState::set_time_scale);
	ClassDB::bind_method(D_METHOD("disable_queue"), &SpineAnimationState::disable_queue);
	ClassDB::bind_method(D_METHOD("enable_queue"), &SpineAnimationState::enable_queue);
	
	ClassDB::bind_method(D_METHOD("set_skeleton_data_res", "skeleton_data_res"), &SpineAnimationState::set_skeleton_data_res);
	ClassDB::bind_method(D_METHOD("get_skeleton_data_res"), &SpineAnimationState::get_skeleton_data_res);
	ClassDB::bind_method(D_METHOD("_on_skeleton_data_changed"), &SpineAnimationState::_on_skeleton_data_changed);
	
	ADD_SIGNAL(MethodInfo("animation_started", PropertyInfo(Variant::OBJECT, "track_entry", PROPERTY_HINT_RESOURCE_TYPE, "SpineTrackEntry")));
	ADD_SIGNAL(MethodInfo("animation_interrupted", PropertyInfo(Variant::OBJECT, "track_entry", PROPERTY_HINT_RESOURCE_TYPE, "SpineTrackEntry")));
	ADD_SIGNAL(MethodInfo("animation_ended", PropertyInfo(Variant::OBJECT, "track_entry", PROPERTY_HINT_RESOURCE_TYPE, "SpineTrackEntry")));
	ADD_SIGNAL(MethodInfo("animation_completed", PropertyInfo(Variant::OBJECT, "track_entry", PROPERTY_HINT_RESOURCE_TYPE, "SpineTrackEntry")));
	ADD_SIGNAL(MethodInfo("animation_disposed", PropertyInfo(Variant::OBJECT, "track_entry", PROPERTY_HINT_RESOURCE_TYPE, "SpineTrackEntry")));
	ADD_SIGNAL(MethodInfo("animation_event", PropertyInfo(Variant::OBJECT, "track_entry", PROPERTY_HINT_RESOURCE_TYPE, "SpineTrackEntry"), PropertyInfo(Variant::OBJECT, "event", PROPERTY_HINT_RESOURCE_TYPE, "SpineEvent")));
	ADD_SIGNAL(MethodInfo("before_update", PropertyInfo(Variant::FLOAT, "delta")));
}

SpineAnimationState::SpineAnimationState() : animation_state(nullptr), sprite(nullptr) {
}

SpineAnimationState::~SpineAnimationState() {
	delete animation_state;
}

void SpineAnimationState::set_spine_sprite(SpineSprite *_sprite) {
	delete animation_state;
	animation_state = nullptr;
	sprite = _sprite;
	if (!sprite || !sprite->get_skeleton_data_res().is_valid() || !sprite->get_skeleton_data_res()->is_skeleton_data_loaded()) return;
	animation_state = new spine::AnimationState(sprite->get_skeleton_data_res()->get_animation_state_data());
	animation_state->setListener(this);
}


bool SpineAnimationState::has_spine_sprite() const
{
	return sprite != nullptr;
}

Ref<SpineSkeletonDataResource> SpineAnimationState::get_skeleton_data_res()
{
	if (sprite)
		return sprite->get_skeleton_data_res();
	
	return skeleton_data_res;
}

void SpineAnimationState::set_skeleton_data_res(Ref<SpineSkeletonDataResource> p_res)
{
	if (skeleton_data_res == p_res)
		return;
	
	if (skeleton_data_res.is_valid())
	{
#if VERSION_MAJOR > 3
		if (skeleton_data_res->is_connected("skeleton_data_changed", callable_mp(this, &SpineAnimationState::_on_skeleton_data_changed)))
			skeleton_data_res->disconnect("skeleton_data_changed", callable_mp(this, &SpineAnimationState::_on_skeleton_data_changed));
#else
		if (skeleton_data_res->is_connected("skeleton_data_changed", this, "_on_skeleton_data_changed"))
			skeleton_data_res->disconnect("skeleton_data_changed", this, "_on_skeleton_data_changed");
#endif
		skeleton_data_res = Ref<SpineSkeletonDataResource>();
	}
	
	if (has_spine_sprite())
		set_spine_sprite(nullptr);
	
	if (p_res.is_null() || !p_res->is_skeleton_data_loaded())
		return;
	
	skeleton_data_res = p_res;
	animation_state = new spine::AnimationState(p_res->get_animation_state_data());
	animation_state->setListener(this);
}

void SpineAnimationState::_on_skeleton_data_changed()
{
	delete animation_state;
	animation_state = nullptr;
	
	if (skeleton_data_res->is_skeleton_data_loaded())
	{
		animation_state = new spine::AnimationState(skeleton_data_res->get_animation_state_data());
		animation_state->setListener(this);
	}
}

void SpineAnimationState::update(float delta) {
	emit_signal(SNAME("before_update"), delta);
	SPINE_CHECK(animation_state, )
	animation_state->update(delta);
}

bool SpineAnimationState::apply(Ref<SpineSkeleton> skeleton) {
	SPINE_CHECK(animation_state, false)
	if (!skeleton->get_spine_object()) return false;
	return animation_state->apply(*(skeleton->get_spine_object()));
}

void SpineAnimationState::clear_tracks() {
	SPINE_CHECK(animation_state, )
	animation_state->clearTracks();
}

void SpineAnimationState::clear_track(int track_id) {
	SPINE_CHECK(animation_state, )
	animation_state->clearTrack(track_id);
}

int SpineAnimationState::get_num_tracks() {
	SPINE_CHECK(animation_state, 0)
	int highest_index = -1;
	for (int i = 0; i < animation_state->getTracks().size(); i++) {
		if (animation_state->getTracks()[i]) highest_index = i;
	}
	return highest_index + 1;
}


Ref<SpineTrackEntry> SpineAnimationState::set_animation(const String &animation_name, bool loop, int track) {
	SPINE_CHECK(animation_state, nullptr)
	auto skeleton_data = animation_state->getData()->getSkeletonData();
	auto animation = skeleton_data->findAnimation(animation_name.utf8().ptr());
	if (!animation) {
		ERR_PRINT(String("Can not find animation: ") + animation_name);
		return nullptr;
	}
	auto track_entry = animation_state->setAnimation(track, animation, loop);
	Ref<SpineTrackEntry> track_entry_ref(memnew(SpineTrackEntry));
	track_entry_ref->set_spine_object(*get_skeleton_data_res(), track_entry);
	return track_entry_ref;
}

Ref<SpineTrackEntry> SpineAnimationState::add_animation(const String &animation_name, float delay, bool loop, int track) {
	SPINE_CHECK(animation_state, nullptr)
	auto skeleton_data = animation_state->getData()->getSkeletonData();
	auto animation = skeleton_data->findAnimation(animation_name.utf8().ptr());
	if (!animation) {
		ERR_PRINT(String("Can not find animation: ") + animation_name);
		return nullptr;
	}
	auto track_entry = animation_state->addAnimation(track, animation, loop, delay);
	Ref<SpineTrackEntry> track_entry_ref(memnew(SpineTrackEntry));
	track_entry_ref->set_spine_object(*get_skeleton_data_res(), track_entry);
	return track_entry_ref;
}

Ref<SpineTrackEntry> SpineAnimationState::set_empty_animation(int track_id, float mix_duration) {
	SPINE_CHECK(animation_state, nullptr)
	auto track_entry = animation_state->setEmptyAnimation(track_id, mix_duration);
	Ref<SpineTrackEntry> track_entry_ref(memnew(SpineTrackEntry));
	track_entry_ref->set_spine_object(*get_skeleton_data_res(), track_entry);
	return track_entry_ref;
}
Ref<SpineTrackEntry> SpineAnimationState::add_empty_animation(int track_id, float mix_duration, float delay) {
	SPINE_CHECK(animation_state, nullptr)
	auto track_entry = animation_state->addEmptyAnimation(track_id, mix_duration, delay);
	Ref<SpineTrackEntry> track_entry_ref(memnew(SpineTrackEntry));
	track_entry_ref->set_spine_object(*get_skeleton_data_res(), track_entry);
	return track_entry_ref;
}
void SpineAnimationState::set_empty_animations(float mix_duration) {
	SPINE_CHECK(animation_state, )
	animation_state->setEmptyAnimations(mix_duration);
}

Ref<SpineTrackEntry> SpineAnimationState::get_current(int track_index) {
	SPINE_CHECK(animation_state, nullptr)
	auto track_entry = animation_state->getCurrent(track_index);
	if (!track_entry) return nullptr;
	Ref<SpineTrackEntry> track_entry_ref(memnew(SpineTrackEntry));
	track_entry_ref->set_spine_object(*get_skeleton_data_res(), track_entry);
	return track_entry_ref;
}

float SpineAnimationState::get_time_scale() {
	SPINE_CHECK(animation_state, 0)
	return animation_state->getTimeScale();
}

void SpineAnimationState::set_time_scale(float time_scale) {
	SPINE_CHECK(animation_state, )
	animation_state->setTimeScale(time_scale);
}

void SpineAnimationState::disable_queue() {
	SPINE_CHECK(animation_state, )
	animation_state->disableQueue();
}

void SpineAnimationState::enable_queue() {
	SPINE_CHECK(animation_state, )
	animation_state->enableQueue();
}

void SpineAnimationState::callback(spine::AnimationState *state, spine::EventType type, spine::TrackEntry *entry, spine::Event *event) {
	Ref<SpineTrackEntry> entry_ref = Ref<SpineTrackEntry>(memnew(SpineTrackEntry));
	entry_ref->set_spine_object(*get_skeleton_data_res(), entry);

	Ref<SpineEvent> event_ref(nullptr);
	if (event) {
		event_ref = Ref<SpineEvent>(memnew(SpineEvent));
		event_ref->set_spine_object(*get_skeleton_data_res(), event);
	}

	switch (type) {
		case spine::EventType_Start:
			emit_signal(SNAME("animation_started"), entry_ref);
			break;
		case spine::EventType_Interrupt:
			emit_signal(SNAME("animation_interrupted"), entry_ref);
			break;
		case spine::EventType_End:
			emit_signal(SNAME("animation_ended"), entry_ref);
			break;
		case spine::EventType_Complete:
			emit_signal(SNAME("animation_completed"), entry_ref);
			break;
		case spine::EventType_Dispose:
			emit_signal(SNAME("animation_disposed"), entry_ref);
			break;
		case spine::EventType_Event:
			emit_signal(SNAME("animation_event"), entry_ref, event_ref);
			break;
	}
}
