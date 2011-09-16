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


#ifndef Space_Explorer_engine_h
#define Space_Explorer_engine_h

#include "misc.h"
#include "tank.h"
#include "vessel.h"

class Engine {
private:
    Eigen::Vector3d _position; // Position du moteur dans le repere du vaisseau
    
    Eigen::Vector3d _ejection; // Vitesse d'ejection du moteur dans le repere du vaisseau
    
    double _debit;             // Debit de carburant en kg/s
    
    Tank* _tank;               // Pointeur vers le reservoir du vaisseau
    
public:
    Engine(Tank* tank, Vessel* vessel, const Eigen::Vector3d& position, const Eigen::Vector3d& vitesse_ejection, double debit);
    ~Engine();
    
    Eigen::Vector3d run(double dt);
    
};

#endif
