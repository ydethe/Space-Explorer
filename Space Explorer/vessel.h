// Copyright (C) 2009  Yann de The
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.



#ifndef Space_Explorer_vessel_h
#define Space_Explorer_vessel_h

#include <vector>

#include "misc.h"
#include "tank.h"
#include "engine_group.h"

class Vessel {
private:
    osg::ref_ptr<osg::PositionAttitudeTransform> _osg_node;
    std::string _nom;
    std::vector<EngineGroup*> _engGroup;
    Tank _tank;
    
    // Physics
    vec3 _vel, _omega;  // _vel exprime en repere inertiel, _omega exprime en repere fusee
    vec3 _force, _torque;
    double _Ixx, _Iyy, _Izz, _Ixz, _Ixy, _Iyz;
    double _mass;
    
public:
    Vessel(osg::ref_ptr<osg::Group>& root, const std::string& nom, const std::string& model_filename);
    ~Vessel();
    
    void setTank(const Tank& tank);
    Tank& obtTank();
    
    void addEngine(ThrusterType type, ThrusterAxis axis, ThrusterSign sign, const Eigen::Vector3d& position, const Eigen::Vector3d& vitesse_ejection, double debit);
    
    std::string obtNom() const;
    
    void addForce(const vec3&); // Force exprimee dans le repere inertiel
    void addTorque(const vec3&); // Moments exprimes dans le repere lie a la fusee
    void resetEfforts();
    void update(double dt);
    
    vec3 obtPosition() const;
    void defPosition(const vec3&);
    
    vec3 obtVitesse() const;
    void defVitesse(const vec3&);
    
    osg::Quat obtAttitude() const;
    void defAttitude(const osg::Quat&);
    
    vec3 obtOmega() const;
    void defOmega(const vec3&);
};

#endif
