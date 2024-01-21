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

#include "SpinePhysicsConstraint.h"
#include "SpineBone.h"
#include "SpineCommon.h"
#include "SpineSprite.h"

void SpinePhysicsConstraint::_bind_methods() {
	ClassDB::bind_method(D_METHOD("update"), &SpinePhysicsConstraint::update);
	ClassDB::bind_method(D_METHOD("get_order"), &SpinePhysicsConstraint::get_order);
	ClassDB::bind_method(D_METHOD("get_data"), &SpinePhysicsConstraint::get_data);
	ClassDB::bind_method(D_METHOD("set_bone", "bone"), &SpinePhysicsConstraint::set_bone);
	ClassDB::bind_method(D_METHOD("get_bone"), &SpinePhysicsConstraint::get_bone);
	
	ClassDB::bind_method(D_METHOD("set_inertia", "inertia"), &SpinePhysicsConstraint::set_inertia);
	ClassDB::bind_method(D_METHOD("get_inertia"), &SpinePhysicsConstraint::get_inertia);
	ClassDB::bind_method(D_METHOD("set_strength", "strength"), &SpinePhysicsConstraint::set_strength);
	ClassDB::bind_method(D_METHOD("get_strength"), &SpinePhysicsConstraint::get_strength);
	ClassDB::bind_method(D_METHOD("set_damping", "damping"), &SpinePhysicsConstraint::set_damping);
	ClassDB::bind_method(D_METHOD("get_damping"), &SpinePhysicsConstraint::get_damping);
	ClassDB::bind_method(D_METHOD("set_mass_inverse", "mass_inverse"), &SpinePhysicsConstraint::set_mass_inverse);
	ClassDB::bind_method(D_METHOD("get_mass_inverse"), &SpinePhysicsConstraint::get_mass_inverse);
	ClassDB::bind_method(D_METHOD("set_wind", "wind"), &SpinePhysicsConstraint::set_wind);
	ClassDB::bind_method(D_METHOD("get_wind"), &SpinePhysicsConstraint::get_wind);
	ClassDB::bind_method(D_METHOD("set_gravity", "gravity"), &SpinePhysicsConstraint::set_gravity);
	ClassDB::bind_method(D_METHOD("get_gravity"), &SpinePhysicsConstraint::get_gravity);
	ClassDB::bind_method(D_METHOD("set_mix", "mix"), &SpinePhysicsConstraint::set_mix);
	ClassDB::bind_method(D_METHOD("get_mix"), &SpinePhysicsConstraint::get_mix);
	
	ClassDB::bind_method(D_METHOD("set_reset", "mix"), &SpinePhysicsConstraint::set_reset);
	ClassDB::bind_method(D_METHOD("get_reset"), &SpinePhysicsConstraint::get_reset);
	
	ClassDB::bind_method(D_METHOD("set_ux", "ux"), &SpinePhysicsConstraint::set_ux);
	ClassDB::bind_method(D_METHOD("get_ux"), &SpinePhysicsConstraint::get_ux);
	ClassDB::bind_method(D_METHOD("set_uy", "uy"), &SpinePhysicsConstraint::set_uy);
	ClassDB::bind_method(D_METHOD("get_uy"), &SpinePhysicsConstraint::get_uy);
	ClassDB::bind_method(D_METHOD("set_cx", "cx"), &SpinePhysicsConstraint::set_cx);
	ClassDB::bind_method(D_METHOD("get_cx"), &SpinePhysicsConstraint::get_cx);
	ClassDB::bind_method(D_METHOD("set_cy", "cy"), &SpinePhysicsConstraint::set_cy);
	ClassDB::bind_method(D_METHOD("get_cy"), &SpinePhysicsConstraint::get_cy);
	ClassDB::bind_method(D_METHOD("set_tx", "tx"), &SpinePhysicsConstraint::set_tx);
	ClassDB::bind_method(D_METHOD("get_tx"), &SpinePhysicsConstraint::get_tx);
	ClassDB::bind_method(D_METHOD("set_ty", "ty"), &SpinePhysicsConstraint::set_ty);
	ClassDB::bind_method(D_METHOD("get_ty"), &SpinePhysicsConstraint::get_ty);
	ClassDB::bind_method(D_METHOD("set_x_offset", "x_offset"), &SpinePhysicsConstraint::set_x_offset);
	ClassDB::bind_method(D_METHOD("get_x_offset"), &SpinePhysicsConstraint::get_x_offset);
	ClassDB::bind_method(D_METHOD("set_x_velocity", "x_offset"), &SpinePhysicsConstraint::set_x_velocity);
	ClassDB::bind_method(D_METHOD("get_x_velocity"), &SpinePhysicsConstraint::get_x_velocity);
	ClassDB::bind_method(D_METHOD("set_y_offset", "y_offset"), &SpinePhysicsConstraint::set_y_offset);
	ClassDB::bind_method(D_METHOD("get_y_offset"), &SpinePhysicsConstraint::get_y_offset);
	ClassDB::bind_method(D_METHOD("set_y_velocity", "y_offset"), &SpinePhysicsConstraint::set_y_velocity);
	ClassDB::bind_method(D_METHOD("get_y_velocity"), &SpinePhysicsConstraint::get_y_velocity);
	ClassDB::bind_method(D_METHOD("set_rotate_offset", "rotate_offset"), &SpinePhysicsConstraint::set_rotate_offset);
	ClassDB::bind_method(D_METHOD("get_rotate_offset"), &SpinePhysicsConstraint::get_rotate_offset);
	ClassDB::bind_method(D_METHOD("set_rotate_velocity", "rotate_velocity"), &SpinePhysicsConstraint::set_rotate_velocity);
	ClassDB::bind_method(D_METHOD("get_rotate_velocity"), &SpinePhysicsConstraint::get_rotate_velocity);
	ClassDB::bind_method(D_METHOD("set_scale_offset", "scale_offset"), &SpinePhysicsConstraint::set_scale_offset);
	ClassDB::bind_method(D_METHOD("get_scale_offset"), &SpinePhysicsConstraint::get_scale_offset);
	ClassDB::bind_method(D_METHOD("set_scale_velocity", "scale_velocity"), &SpinePhysicsConstraint::set_scale_velocity);
	ClassDB::bind_method(D_METHOD("get_scale_velocity"), &SpinePhysicsConstraint::get_scale_velocity);
	ClassDB::bind_method(D_METHOD("set_active", "active"), &SpinePhysicsConstraint::set_active);
	ClassDB::bind_method(D_METHOD("is_active"), &SpinePhysicsConstraint::is_active);
	ClassDB::bind_method(D_METHOD("set_remaining", "remaining"), &SpinePhysicsConstraint::set_remaining);
	ClassDB::bind_method(D_METHOD("get_remaining"), &SpinePhysicsConstraint::get_remaining);
	ClassDB::bind_method(D_METHOD("set_last_time", "last_time"), &SpinePhysicsConstraint::set_last_time);
	ClassDB::bind_method(D_METHOD("get_last_time"), &SpinePhysicsConstraint::get_last_time);
	ClassDB::bind_method(D_METHOD("reset"), &SpinePhysicsConstraint::reset);
	ClassDB::bind_method(D_METHOD("set_to_setup_pose"), &SpinePhysicsConstraint::set_to_setup_pose);
	
	ClassDB::bind_method(D_METHOD("get_physics_update_mode"), &SpinePhysicsConstraint::get_physics_update_mode);
	ClassDB::bind_method(D_METHOD("set_physics_update_mode", "v"), &SpinePhysicsConstraint::set_physics_update_mode);
	
	ADD_PROPERTY(PropertyInfo(Variant::INT, "physics_update_mode", PROPERTY_HINT_ENUM, "None,Reset,Update,Pose", PROPERTY_USAGE_DEFAULT), "set_physics_update_mode", "get_physics_update_mode");
}

void SpinePhysicsConstraint::update() {
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->update(physics_update_mode);
}

int SpinePhysicsConstraint::get_order() {
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getOrder();
}

Ref<SpinePhysicsConstraintData> SpinePhysicsConstraint::get_data() {
	SPINE_CHECK(get_spine_object(), nullptr)
	auto &constraintData = get_spine_object()->getData();
	Ref<SpinePhysicsConstraintData> spineConstraintData(memnew(SpinePhysicsConstraintData));
	spineConstraintData->set_spine_object(*get_spine_owner()->get_skeleton_data_res(), &constraintData);
	return spineConstraintData;
}

void SpinePhysicsConstraint::set_bone(Ref<SpineBone> p_bone)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setBone(p_bone.is_valid() && p_bone->get_spine_object() ? p_bone->get_spine_object() : nullptr);
}

Ref<SpineBone> SpinePhysicsConstraint::get_bone()
{
	SPINE_CHECK(get_spine_object(), nullptr)
	auto bone = get_spine_object()->getBone();
	if (!bone)
		return nullptr;
	
	Ref<SpineBone> spineBone(memnew(SpineBone));
	spineBone->set_spine_object(get_spine_owner(), bone);
	return spineBone;
}

void SpinePhysicsConstraint::set_inertia(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setInertia(p_value);
}

float SpinePhysicsConstraint::get_inertia()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getInertia();
}

void SpinePhysicsConstraint::set_strength(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setStrength(p_value);
}

float SpinePhysicsConstraint::get_strength()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getStrength();
}

void SpinePhysicsConstraint::set_damping(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setDamping(p_value);
}

float SpinePhysicsConstraint::get_damping()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getDamping();
}

void SpinePhysicsConstraint::set_mass_inverse(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setMassInverse(p_value);
}

float SpinePhysicsConstraint::get_mass_inverse()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getMassInverse();
}

void SpinePhysicsConstraint::set_wind(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setWind(p_value);
}

float SpinePhysicsConstraint::get_wind()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getWind();
}

void SpinePhysicsConstraint::set_gravity(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setGravity(p_value);
}

float SpinePhysicsConstraint::get_gravity()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getGravity();
}

void SpinePhysicsConstraint::set_mix(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setMix(p_value);
}

float SpinePhysicsConstraint::get_mix()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getMix();
}

void SpinePhysicsConstraint::set_reset(bool p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setReset(p_value);
}

bool SpinePhysicsConstraint::get_reset()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getReset();
}

void SpinePhysicsConstraint::set_ux(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setUx(p_value);
}

float SpinePhysicsConstraint::get_ux()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getUx();
}

void SpinePhysicsConstraint::set_uy(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setUy(p_value);
}

float SpinePhysicsConstraint::get_uy()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getUy();
}

void SpinePhysicsConstraint::set_cx(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setCx(p_value);
}

float SpinePhysicsConstraint::get_cx()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getCx();
}

void SpinePhysicsConstraint::set_cy(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setCy(p_value);
}

float SpinePhysicsConstraint::get_cy()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getCy();
}

void SpinePhysicsConstraint::set_tx(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setTx(p_value);
}

float SpinePhysicsConstraint::get_tx()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getTx();
}

void SpinePhysicsConstraint::set_ty(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setTy(p_value);
}

float SpinePhysicsConstraint::get_ty()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getTy();
}


void SpinePhysicsConstraint::set_x_offset(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setXOffset(p_value);
}

float SpinePhysicsConstraint::get_x_offset()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getXOffset();
}

void SpinePhysicsConstraint::set_x_velocity(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setXVelocity(p_value);
}

float SpinePhysicsConstraint::get_x_velocity()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getXVelocity();
}

void SpinePhysicsConstraint::set_y_offset(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setYOffset(p_value);
}

float SpinePhysicsConstraint::get_y_offset()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getYOffset();
}

void SpinePhysicsConstraint::set_y_velocity(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setYVelocity(p_value);
}

float SpinePhysicsConstraint::get_y_velocity()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getYVelocity();
}

void SpinePhysicsConstraint::set_rotate_offset(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setRotateOffset(p_value);
}

float SpinePhysicsConstraint::get_rotate_offset()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getRotateOffset();
}

void SpinePhysicsConstraint::set_rotate_velocity(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setRotateVelocity(p_value);
}
float SpinePhysicsConstraint::get_rotate_velocity()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getRotateVelocity();
}

void SpinePhysicsConstraint::set_scale_offset(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setScaleOffset(p_value);
}

float SpinePhysicsConstraint::get_scale_offset()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getScaleOffset();
}

void SpinePhysicsConstraint::set_scale_velocity(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setScaleVelocity(p_value);
}

float SpinePhysicsConstraint::get_scale_velocity()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getScaleVelocity();
}

void SpinePhysicsConstraint::set_active(bool p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setActive(p_value);
}

bool SpinePhysicsConstraint::is_active()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->isActive();
}

void SpinePhysicsConstraint::set_remaining(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setRemaining(p_value);
}

float SpinePhysicsConstraint::get_remaining()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getRemaining();
}

void SpinePhysicsConstraint::set_last_time(float p_value)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setLastTime(p_value);
}

float SpinePhysicsConstraint::get_last_time()
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_object()->getLastTime();
}

void SpinePhysicsConstraint::reset()
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->reset();
}

void SpinePhysicsConstraint::set_to_setup_pose()
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_object()->setToSetupPose();
}

SpineConstant::PhysicsUpdateMode SpinePhysicsConstraint::get_physics_update_mode() const
{
	return (SpineConstant::PhysicsUpdateMode)physics_update_mode;
}

void SpinePhysicsConstraint::set_physics_update_mode(SpineConstant::PhysicsUpdateMode p_mode)
{
	physics_update_mode = (spine::Physics)p_mode;
}


