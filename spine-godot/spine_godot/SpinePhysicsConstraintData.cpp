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

#include "SpinePhysicsConstraintData.h"
#include "SpineCommon.h"

void SpinePhysicsConstraintData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_bone", "bone"), &SpinePhysicsConstraintData::set_bone);
	ClassDB::bind_method(D_METHOD("get_bone"), &SpinePhysicsConstraintData::get_bone);
	
	ClassDB::bind_method(D_METHOD("set_x", "x"), &SpinePhysicsConstraintData::set_x);
	ClassDB::bind_method(D_METHOD("get_x"), &SpinePhysicsConstraintData::get_x);
	ClassDB::bind_method(D_METHOD("set_y", "y"), &SpinePhysicsConstraintData::set_y);
	ClassDB::bind_method(D_METHOD("get_y"), &SpinePhysicsConstraintData::get_y);
	ClassDB::bind_method(D_METHOD("set_rotate", "rotate"), &SpinePhysicsConstraintData::set_rotate);
	ClassDB::bind_method(D_METHOD("get_rotate"), &SpinePhysicsConstraintData::get_rotate);
	ClassDB::bind_method(D_METHOD("set_scale_x", "scale_x"), &SpinePhysicsConstraintData::set_scale_x);
	ClassDB::bind_method(D_METHOD("get_scale_x"), &SpinePhysicsConstraintData::get_scale_x);
	ClassDB::bind_method(D_METHOD("set_shear_x", "shear_x"), &SpinePhysicsConstraintData::set_shear_x);
	ClassDB::bind_method(D_METHOD("get_shear_x"), &SpinePhysicsConstraintData::get_shear_x);
	
	ClassDB::bind_method(D_METHOD("set_step", "step"), &SpinePhysicsConstraintData::set_step);
	ClassDB::bind_method(D_METHOD("get_step"), &SpinePhysicsConstraintData::get_step);
	
	ClassDB::bind_method(D_METHOD("set_inertia", "inertia"), &SpinePhysicsConstraintData::set_inertia);
	ClassDB::bind_method(D_METHOD("get_inertia"), &SpinePhysicsConstraintData::get_inertia);
	ClassDB::bind_method(D_METHOD("set_strength", "strength"), &SpinePhysicsConstraintData::set_strength);
	ClassDB::bind_method(D_METHOD("get_strength"), &SpinePhysicsConstraintData::get_strength);
	ClassDB::bind_method(D_METHOD("set_damping", "damping"), &SpinePhysicsConstraintData::set_damping);
	ClassDB::bind_method(D_METHOD("get_damping"), &SpinePhysicsConstraintData::get_damping);
	ClassDB::bind_method(D_METHOD("set_mass_inverse", "mass_inverse"), &SpinePhysicsConstraintData::set_mass_inverse);
	ClassDB::bind_method(D_METHOD("get_mass_inverse"), &SpinePhysicsConstraintData::get_mass_inverse);
	ClassDB::bind_method(D_METHOD("set_wind", "wind"), &SpinePhysicsConstraintData::set_wind);
	ClassDB::bind_method(D_METHOD("get_wind"), &SpinePhysicsConstraintData::get_wind);
	ClassDB::bind_method(D_METHOD("set_gravity", "gravity"), &SpinePhysicsConstraintData::set_gravity);
	ClassDB::bind_method(D_METHOD("get_gravity"), &SpinePhysicsConstraintData::get_gravity);
	ClassDB::bind_method(D_METHOD("set_mix", "mix"), &SpinePhysicsConstraintData::set_mix);
	ClassDB::bind_method(D_METHOD("get_mix"), &SpinePhysicsConstraintData::get_mix);
	
	ClassDB::bind_method(D_METHOD("set_inertia_global", "inertia"), &SpinePhysicsConstraintData::set_inertia_global);
	ClassDB::bind_method(D_METHOD("is_inertia_global"), &SpinePhysicsConstraintData::is_inertia_global);
	ClassDB::bind_method(D_METHOD("set_strength_global", "strength"), &SpinePhysicsConstraintData::set_strength_global);
	ClassDB::bind_method(D_METHOD("is_strength_global"), &SpinePhysicsConstraintData::is_strength_global);
	ClassDB::bind_method(D_METHOD("set_damping_global", "damping"), &SpinePhysicsConstraintData::set_damping_global);
	ClassDB::bind_method(D_METHOD("is_damping_global"), &SpinePhysicsConstraintData::is_damping_global);
	ClassDB::bind_method(D_METHOD("set_mass_global", "mass"), &SpinePhysicsConstraintData::set_mass_global);
	ClassDB::bind_method(D_METHOD("is_mass_global"), &SpinePhysicsConstraintData::is_mass_global);
	ClassDB::bind_method(D_METHOD("set_wind_global", "wind"), &SpinePhysicsConstraintData::set_wind_global);
	ClassDB::bind_method(D_METHOD("is_wind_global"), &SpinePhysicsConstraintData::is_wind_global);
	ClassDB::bind_method(D_METHOD("set_gravity_global", "gravity"), &SpinePhysicsConstraintData::set_gravity_global);
	ClassDB::bind_method(D_METHOD("is_gravity_global"), &SpinePhysicsConstraintData::is_gravity_global);
	ClassDB::bind_method(D_METHOD("set_mix_global", "mix"), &SpinePhysicsConstraintData::set_mix_global);
	ClassDB::bind_method(D_METHOD("is_mix_global"), &SpinePhysicsConstraintData::is_mix_global);
}

void SpinePhysicsConstraintData::set_bone(Ref<SpineBoneData> p_bone)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setBone(p_bone.is_valid() && p_bone->get_spine_object() ? p_bone->get_spine_object() : nullptr);
}

Ref<SpineBoneData> SpinePhysicsConstraintData::get_bone() const
{
	SPINE_CHECK(get_spine_object(), nullptr)
	spine::BoneData* pBoneData = get_spine_constraint_data()->getBone();
	if (!pBoneData)
		return nullptr;
	
	Ref<SpineBoneData> spineBoneData(memnew(SpineBoneData));
	spineBoneData->set_spine_object(get_spine_owner(), pBoneData);
	return spineBoneData;
}

void SpinePhysicsConstraintData::set_x(float p_x)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setX(p_x);
}

float SpinePhysicsConstraintData::get_x() const
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_constraint_data()->getX();
}

void SpinePhysicsConstraintData::set_y(float p_y)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setY(p_y);
}

float SpinePhysicsConstraintData::get_y() const
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_constraint_data()->getY();
}

void SpinePhysicsConstraintData::set_rotate(float p_rotate)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setRotate(p_rotate);
}

float SpinePhysicsConstraintData::get_rotate() const
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_constraint_data()->getRotate();
}

void SpinePhysicsConstraintData::set_scale_x(float p_scale_x)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setScaleX(p_scale_x);
}

float SpinePhysicsConstraintData::get_scale_x() const
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_constraint_data()->getScaleX();
}

void SpinePhysicsConstraintData::set_shear_x(float p_shear_x)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setShearX(p_shear_x);
}

float SpinePhysicsConstraintData::get_shear_x() const
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_constraint_data()->getShearX();
}

void SpinePhysicsConstraintData::set_step(float p_step)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setStep(p_step);
}

float SpinePhysicsConstraintData::get_step() const
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_constraint_data()->getStep();
}

void SpinePhysicsConstraintData::set_inertia(float p_inertia)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setInertia(p_inertia);
}

float SpinePhysicsConstraintData::get_inertia() const
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_constraint_data()->getInertia();
}

void SpinePhysicsConstraintData::set_strength(float p_strength)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setStrength(p_strength);
}

float SpinePhysicsConstraintData::get_strength() const
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_constraint_data()->getStrength();
}

void SpinePhysicsConstraintData::set_damping(float p_damping)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setDamping(p_damping);
}

float SpinePhysicsConstraintData::get_damping() const
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_constraint_data()->getDamping();
}

void SpinePhysicsConstraintData::set_mass_inverse(float p_mass_inverse)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setMassInverse(p_mass_inverse);
}

float SpinePhysicsConstraintData::get_mass_inverse() const
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_constraint_data()->getMassInverse();
}

void SpinePhysicsConstraintData::set_wind(float p_wind)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setWind(p_wind);
}

float SpinePhysicsConstraintData::get_wind() const
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_constraint_data()->getWind();
}

void SpinePhysicsConstraintData::set_gravity(float p_gravity)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setGravity(p_gravity);
}

float SpinePhysicsConstraintData::get_gravity() const
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_constraint_data()->getGravity();
}

void SpinePhysicsConstraintData::set_mix(float p_mix)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setMix(p_mix);
}

float SpinePhysicsConstraintData::get_mix() const
{
	SPINE_CHECK(get_spine_object(), 0)
	return get_spine_constraint_data()->getMix();
}

void SpinePhysicsConstraintData::set_inertia_global(bool p_inertia_global)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setInertiaGlobal(p_inertia_global);
}

bool SpinePhysicsConstraintData::is_inertia_global() const
{
	SPINE_CHECK(get_spine_object(), false)
	return get_spine_constraint_data()->isInertiaGlobal();
}

void SpinePhysicsConstraintData::set_strength_global(bool p_strength_global)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setStrengthGlobal(p_strength_global);
}

bool SpinePhysicsConstraintData::is_strength_global() const
{
	SPINE_CHECK(get_spine_object(), false)
	return get_spine_constraint_data()->isStrengthGlobal();
}

void SpinePhysicsConstraintData::set_damping_global(bool p_damping_global)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setDampingGlobal(p_damping_global);
}

bool SpinePhysicsConstraintData::is_damping_global() const
{
	SPINE_CHECK(get_spine_object(), false)
	return get_spine_constraint_data()->isDampingGlobal();
}

void SpinePhysicsConstraintData::set_mass_global(bool p_mass_global)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setMassGlobal(p_mass_global);
}

bool SpinePhysicsConstraintData::is_mass_global() const
{
	SPINE_CHECK(get_spine_object(), false)
	return get_spine_constraint_data()->isMassGlobal();
}

void SpinePhysicsConstraintData::set_wind_global(bool p_wind_global)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setWindGlobal(p_wind_global);
}

bool SpinePhysicsConstraintData::is_wind_global() const
{
	SPINE_CHECK(get_spine_object(), false)
	return get_spine_constraint_data()->isWindGlobal();
}

void SpinePhysicsConstraintData::set_gravity_global(bool p_gravity_global)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setGravityGlobal(p_gravity_global);
}

bool SpinePhysicsConstraintData::is_gravity_global() const
{
	SPINE_CHECK(get_spine_object(), false)
	return get_spine_constraint_data()->isGravityGlobal();
}

void SpinePhysicsConstraintData::set_mix_global(bool p_mix_global)
{
	SPINE_CHECK(get_spine_object(), )
	get_spine_constraint_data()->setMixGlobal(p_mix_global);
}

bool SpinePhysicsConstraintData::is_mix_global() const
{
	SPINE_CHECK(get_spine_object(), false)
	return get_spine_constraint_data()->isMixGlobal();
}
