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


#include "engine_group.h"

EngineGroup::EngineGroup(Vessel* vessel, ThrusterType type, ThrusterAxis axis, ThrusterSign sign) : _vessel(vessel), _type(type), _axis(axis), _sgn(sign) {
    
}

EngineGroup::~EngineGroup() {

}

void EngineGroup::createEngine(const Eigen::Vector3d& position, const Eigen::Vector3d& vitesse_ejection, double debit) {
    Engine* eng = new Engine(_vessel->obtTank(), _vessel, position, vitesse_ejection, debit);
    _engines.push_back(eng);
    std::cout << "Moteur cree" << std::endl;
}

Eigen::Vector3d EngineGroup::run(double dt) {
    std::vector<Engine*>::iterator it;
    Eigen::Vector3d com;
    Eigen::Vector3d force;
    Eigen::Vector3d torque;
    
    Eigen::Vector3d tmp_force;
    Eigen::Vector3d tmp_torque;
    
    for (it = _engines.begin(); it != _engines.end(); ++it) {
        tmp_force = (*it)->run(dt);
        force += tmp_force;
    }
    
    return force;
}

