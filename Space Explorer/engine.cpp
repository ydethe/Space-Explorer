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


#include "engine.h"
#include "vessel.h"

Engine::Engine(Vessel* vessel, const vec3& position, const vec3& vitesse_ejection, double debit) : _vessel(vessel), _debit(debit), _level(0.), _position(position), _ejection(vitesse_ejection) {
    
}

Engine::~Engine() {
    
}

vec3 Engine::obtPosition() const {
    return _position;
}

void Engine::setLevel(float level) {
    if ( level > 1. || level < 0.)
        std::cerr << "Level invalide : " << level << std::endl;
    _level = level;
}

float Engine::getLevel() const {
    return _level;
}

vec3 Engine::run(double dt) {
    vec3 force;
    double dm_demande = _level*_debit*dt;
    double dm_fourni;
    
    dm_fourni = _vessel->obtTank().utilise(dm_demande);
    
    osg::notify( osg::ALWAYS ) << "Ve:" << _ejection[0] << "," << _ejection[1] << "," << _ejection[2] << "\td:" << _debit << "\ttau:" << _level << "\tdm_f:" << dm_fourni << "\tdm_d:" << dm_demande << std::endl;
    
    if (dm_demande == 0.) {
        std::cout << "dm_demande == 0." << std::endl;
        force = vec3(0.,0.,0.);
    } else
        force = -_ejection*_debit*_level*dm_fourni/dm_demande;
    _vessel->decrMass(dm_fourni);
    
    osg::notify( osg::ALWAYS ) << "Force : " << force[0] << "," << force[1] << "," << force[2] << std::endl;
    return force;
}

