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


#ifndef Space_Explorer_tank_h
#define Space_Explorer_tank_h

#include "misc.h"

class Tank {
private:
    std::string _nom;
    
    double _rho;      // Masse volumique du carburant
    
    double _volume;   // Volume courant
    
    double _capacite; // Volume total
    
public:
    Tank();
    Tank(const std::string& nom, double rho, double capacite, double volume);
    ~Tank();
    
    bool utilise(double volume_consomme);
    
};

#endif
