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
#include <string>

#include "engine.h"

typedef enum {RCS_LIN_X_POS, RCS_LIN_X_NEG, RCS_LIN_Y_POS, RCS_LIN_Y_NEG, RCS_LIN_Z_POS, RCS_LIN_Z_NEG, RCS_ROT_X_POS, RCS_ROT_X_NEG, RCS_ROT_Y_POS, RCS_ROT_Y_NEG, RCS_ROT_Z_POS, RCS_ROT_Z_NEG, MAIN, HOVER} ThrusterType;

typedef struct {vec3 force; vec3 torque;} Effort;

ThrusterType from_string(const char* typeName);

class EngineGroup {
private:
    std::vector<Engine*> _engines;
    ThrusterType _type;
    
    Vessel* _vessel;           // Vaisseau auquel le moteur appartient
    
public:
    EngineGroup(Vessel* vessel, ThrusterType type);
    ~EngineGroup();
    
    void createEngine(const vec3& position, const vec3& vitesse_ejection, double debit);
    
    void setLevel(float level);
    float getLevel() const;
    
    Effort run(double dt);
    
};

#endif
