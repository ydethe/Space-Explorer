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

Engine::Engine(Tank* tank, Vessel* vessel, const Eigen::Vector3d& position, const Eigen::Vector3d& vitesse_ejection, double debit) : _debit(debit), _tank(tank) {
    
}

Engine::~Engine() {
    
}

Eigen::Vector3d Engine::run(double dt) {
    Eigen::Vector3d force;
    
    if ( _tank->utilise(_debit*dt) )
        force = _ejection*_debit;
    
    return force;
}

