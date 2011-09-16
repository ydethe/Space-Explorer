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


#include "tank.h"

Tank::Tank() : _nom("[Uninitialized]"), _rho(1.), _capacite(1.), _volume(0.) {
    
}

Tank::Tank(const std::string& nom, double rho, double capacite, double volume) : _nom(nom), _rho(rho), _capacite(capacite), _volume(volume) {
    
}

Tank::~Tank() {
    
}
bool Tank::utilise(double masse_consomme) {
    double dV;
    double volume_consomme = masse_consomme/_rho;
    bool not_empty;
    
    if (_volume > volume_consomme) {
        dV = volume_consomme;
        _volume -= volume_consomme;
        not_empty = true;
    } else {
        dV = _volume;
        _volume = 0.;
        not_empty = false;
    }
    
    return not_empty;
}

