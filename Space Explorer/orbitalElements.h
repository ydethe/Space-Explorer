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



#ifndef Space_Explorer_orbitalElements_h
#define Space_Explorer_orbitalElements_h

typedef struct {
    double inclination;
    double eccentricity;
    double ascendingNodeLongitude;
    double periapsisArgument;
    double meanAnomaly;
    double orbitalPeriod;
    double trueAnomaly;
    double semiMajorAxis;
    double semiMinorAxis;
    double betaAngle;
    double linearEccentricity;
    double periapsisDistance;
    double apoapsisDistance;
    double eccentricAnomaly;
    double meanLongitude;
    double trueLongitude;
} OrbitalElements;

#endif
