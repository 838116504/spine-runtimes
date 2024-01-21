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

#pragma once

#include "SpineConstraintData.h"
#include "SpineBoneData.h"
#include <spine/PhysicsConstraintData.h>

class SpinePhysicsConstraintData : public SpineConstraintData {
	GDCLASS(SpinePhysicsConstraintData, SpineConstraintData)

	spine::PhysicsConstraintData *get_spine_constraint_data() const { return (spine::PhysicsConstraintData *) get_spine_object(); }

protected:
	static void _bind_methods();

public:
	void set_bone(Ref<SpineBoneData> p_bone);

	Ref<SpineBoneData> get_bone() const;

	void set_x(float p_x);

	float get_x() const;

	void set_y(float p_y);

	float get_y() const;

	void set_rotate(float p_rotate);

	float get_rotate() const;

	void set_scale_x(float p_scale_x);

	float get_scale_x() const;

	void set_shear_x(float p_shear_x);

	float get_shear_x() const;

	void set_step(float p_step);

	float get_step() const;

	void set_inertia(float p_inertia);

	float get_inertia() const;

	void set_strength(float p_strength);

	float get_strength() const;

	void set_damping(float p_damping);

	float get_damping() const;

	void set_mass_inverse(float p_mass_inverse);

	float get_mass_inverse() const;

	void set_wind(float p_wind);

	float get_wind() const;

	void set_gravity(float p_gravity);

	float get_gravity() const;

	void set_mix(float p_mix);

	float get_mix() const;

	void set_inertia_global(bool p_inertia_global);

	bool is_inertia_global() const;

	void set_strength_global(bool p_strength_global);

	bool is_strength_global() const;

	void set_damping_global(bool p_damping_global);

	bool is_damping_global() const;

	void set_mass_global(bool p_mass_global);

	bool is_mass_global() const;

	void set_wind_global(bool p_wind_global);

	bool is_wind_global() const;

	void set_gravity_global(bool p_gravity_global);

	bool is_gravity_global() const;

	void set_mix_global(bool p_mix_global);

	bool is_mix_global() const;

};
