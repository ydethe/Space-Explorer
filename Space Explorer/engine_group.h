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


#ifndef Space_Explorer_engine_group_h
#define Space_Explorer_engine_group_h

#include <vector>

#include "engine.h"

typedef enum {RCS_LIN, RCS_ROT, MAIN, HOVER} ThrusterType;
typedef enum {X, Y, Z} ThrusterAxis;
typedef enum {POSITIVE, NEGATIVE} ThrusterSign;

class EngineGroup {
private:
    std::vector<Engine*> _engines;
    ThrusterType _type;
    ThrusterAxis _axis;
    ThrusterSign _sgn;
    
    Vessel* _vessel;           // Vaisseau auquel le moteur appartient
    
public:
    EngineGroup(Vessel* vessel, ThrusterType type, ThrusterAxis axis, ThrusterSign sign);
    ~EngineGroup();
    
    void createEngine(const Eigen::Vector3d& position, const Eigen::Vector3d& vitesse_ejection, double debit);
    Eigen::Vector3d run(double dt);
    
};

#endif
