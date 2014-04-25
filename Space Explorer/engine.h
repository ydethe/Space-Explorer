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

class Vessel;

class Engine {
private:
    vec3 _position; // Position du moteur dans le repere du vaisseau par rapport à son CdG
    
    vec3 _ejection; // Vitesse d'ejection du moteur dans le repere du vaisseau. Donne l'opposé de la force de poussée
    
    double _debit;  // Debit de carburant en kg/s
    
    Vessel* _vessel;
    
    float _level;
    
public:
    Engine(Vessel* vessel, const vec3& position, const vec3& vitesse_ejection, double debit);
    ~Engine();
    
    vec3 obtPosition() const;
    
    void setLevel(float);
    float getLevel() const;
    
    vec3 run(double dt);
    
};

#endif
