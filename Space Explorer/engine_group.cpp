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

ThrusterType from_string(const char* typeName) {
    if (std::string(typeName) == "RCS_LIN_X_POS")
        return RCS_LIN_X_POS;
            
    if (std::string(typeName) == "RCS_LIN_X_NEG")
        return RCS_LIN_X_NEG;
        
    if (std::string(typeName) == "RCS_LIN_Y_POS")
        return RCS_LIN_Y_POS;
        
    if (std::string(typeName) == "RCS_LIN_Y_NEG")
        return RCS_LIN_Y_POS;
        
    if (std::string(typeName) == "RCS_LIN_Z_POS")
        return RCS_LIN_Z_POS;
        
    if (std::string(typeName) == "RCS_LIN_Z_NEG")
        return RCS_LIN_Z_POS;
        
    if (std::string(typeName) == "RCS_ROT_X_POS")
        return RCS_LIN_X_POS;
        
    if (std::string(typeName) == "RCS_ROT_X_NEG")
        return RCS_LIN_X_NEG;
        
    if (std::string(typeName) == "RCS_ROT_Y_POS")
        return RCS_LIN_Y_POS;
        
    if (std::string(typeName) == "RCS_ROT_Y_NEG")
        return RCS_LIN_Y_POS;
        
    if (std::string(typeName) == "RCS_ROT_Z_POS")
        return RCS_LIN_Z_POS;
        
    if (std::string(typeName) == "RCS_ROT_Z_NEG")
        return RCS_LIN_Z_POS;
        
    if (std::string(typeName) == "MAIN")
        return MAIN;
        
    if (std::string(typeName) == "HOVER")
        return HOVER;
}

EngineGroup::EngineGroup(Vessel* vessel, ThrusterType type) : _vessel(vessel), _type(type) {
    
}

EngineGroup::~EngineGroup() {
    std::vector<Engine*>::iterator it;
    
    for (it = _engines.begin(); it != _engines.end(); it++)
        delete (*it);
}

void EngineGroup::createEngine(const vec3& position, const vec3& vitesse_ejection, double debit) {
    Engine* eng = new Engine(_vessel, position, vitesse_ejection, debit);
    _engines.push_back(eng);
    osg::notify( osg::ALWAYS ) << "Moteur cree" << std::endl;
}

void EngineGroup::setLevel(float level) {
    std::vector<Engine*>::iterator it;
    
    for (it = _engines.begin(); it != _engines.end(); it++)
        (*it)->setLevel(level);
}

float EngineGroup::getLevel() const {
    return _engines[0]->getLevel();
}

Effort EngineGroup::run(double dt) {
    std::vector<Engine*>::iterator it;
    vec3 force = vec3(0.,0.,0.);
    vec3 torque = vec3(0.,0.,0.);
    Effort effort;
    
    vec3 tmp_force;
    vec3 tmp_torque;
    
    for (it = _engines.begin(); it != _engines.end(); ++it) {
        tmp_force = (*it)->run(dt);
        tmp_torque = cross((*it)->obtPosition(), tmp_force);
        
        force += tmp_force;
        torque += tmp_torque;
    }
    
    effort.force = force;
    effort.torque = torque;
    
    return effort;
}

