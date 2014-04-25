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


#include "vessel.h"

/*
 The body frame uses the X axis for forward and aft, with + to the front. The Y axis is side to side with + to the right. The Z axis is up and down, with + being down. The origin of this frame is the Center of Gravity (CG), about which the aircraft forces and moments are summed and the resulting accelerations are integrated to get velocities
 */

Vessel::Vessel(osg::ref_ptr<osg::Group>& root, const std::string& name, const std::string& model_filename) : _nom(name) {
    
    // Graphics
    _osg_node = new osg::PositionAttitudeTransform();
    
    osg::ref_ptr<osg::Node> node = osgDB::readNodeFile( model_filename );
	if( !node.valid() ) {
		osg::notify( osg::FATAL ) << "Can't find " << model_filename << std::endl;
		exit( 0 );
	}
    else
        osg::notify( osg::ALWAYS ) << _nom << " imported" << std::endl;
    osgUtil::Optimizer optimizer;
    optimizer.optimize(node.get());
    osg::notify( osg::ALWAYS ) << _nom << " optimized" << std::endl;
    
    _osg_node->addChild( node.get() );
    root->addChild( _osg_node.get() );
    
    // Physics
    _Ixx = 1292310.08;
    _Iyy = 10121289.4;
    _Izz = 10504308.;
    _Ixz = 190230.749*0.;
    _Ixy = 0.;
    _Iyz = 0.;
    
    _mass = 109000.;
    
    this->defPosition(vec3());
    this->defVitesse(vec3());
    this->defAttitude(osg::Quat(0.,0.,0., 1.));
    this->defOmega(vec3());
    _force = vec3();
    _torque = vec3();
    
}

Vessel::~Vessel() {
    std::map<ThrusterType, EngineGroup*>::iterator itGrp;
    
    for (itGrp = _engGroup.begin(); itGrp != _engGroup.end(); itGrp++)
        delete itGrp->second;
    
}

void Vessel::setTank(const Tank& tank) {
    _tank = tank;
}

Tank& Vessel::obtTank() {
    return _tank;
}

void Vessel::addEngine(ThrusterType type, const vec3& position, const vec3& vitesse_ejection, double debit) {
    std::map<ThrusterType, EngineGroup*>::iterator it = _engGroup.find(type);
    
    // Si le groupe identifié par type existe déjà, on ajoute le moteur dans celui-ci
    if(it != _engGroup.end()) {
        osg::notify( osg::ALWAYS ) << "Moteur ajouté à un groupe déjà existant" << std::endl;
        it->second->createEngine(position, vitesse_ejection, debit);
    // Sinon, on crée un groupe avec cet identifiant
    } else {
        osg::notify( osg::ALWAYS ) << "Creation d'un groupe de moteurs" << std::endl;
        EngineGroup* grp = new EngineGroup(this, type);
        grp->createEngine(position, vitesse_ejection, debit);
        _engGroup[type] = grp;
    }
}


void Vessel::setLevel(ThrusterType type, float level) {
    _engGroup[type]->setLevel(level);
}

float Vessel::getLevel(ThrusterType type) {
    return _engGroup[type]->getLevel();
}

void Vessel::addForce(const vec3& force) { // Force exprimee dans le repere inertiel
    _force = _force + force;
}

void Vessel::addTorque(const vec3& torque) { // Moments exprimes dans le repere lie a la fusee
    _torque = _torque + torque;
}

void Vessel::resetEfforts() {
    _force = vec3();
    _torque = vec3();
}

void Vessel::update(double dt) {
    osg::notify( osg::ALWAYS ) << "Pos : " << this->obtPosition()[0] << "," << this->obtPosition()[1] << "," << this->obtPosition()[2] << std::endl;
    
    std::map<ThrusterType,EngineGroup*>::iterator it;
    Effort effort;
    
    for (it = _engGroup.begin(); it != _engGroup.end(); it++) {
        effort = it->second->run(dt);
        this->addForce(effort.force);
        this->addTorque(effort.torque);
        osg::notify( osg::ALWAYS ) << "Force : " << _force[0] << "," << _force[1] << "," << _force[2] << std::endl;
    }
    
    std::cout << "M:" << _mass << std::endl;
    
    // Translation
    vec3 new_pos, new_vel;
    
    new_pos = this->obtPosition() + _vel*dt;
    new_vel = this->obtVitesse() + _force*dt/_mass;
    
    this->defPosition(new_pos);
    this->defVitesse(new_vel);
    
    _force = vec3(0.,0.,0.);
    
    // Rotation
    double p,q,r;
    double dp,dq,dr;
    
    osg::Quat att = this->obtAttitude();
    double q0, q1, q2, q3;
    double dq0, dq1, dq2, dq3;
    
    q0 = att.w();
    q1 = att.x();
    q2 = att.y();
    q3 = att.z();
    
    p = _omega[0];
    q = _omega[1];
    r = _omega[2];
    
    dp = (_torque[0] + (_Iyy-_Izz)*q*r + _Ixy*(_torque[1]-r*p) + _Iyz*(q*q-r*r) + _Ixz*(_torque[2]+p*q))/_Ixx;
    dq = (_torque[1] + (_Izz-_Ixx)*r*p + _Iyz*(_torque[2]-p*q) + _Ixz*(r*r-p*p) + _Ixy*(_torque[0]+p*q))/_Iyy;
    dr = (_torque[2] + (_Ixx-_Iyy)*p*q + _Ixz*(_torque[0]-q*r) + _Ixy*(p*p-q*q) + _Iyz*(_torque[1]+r*p))/_Izz;
    
    dq0 = 0.5*(-p*q1 - q*q2 - r*q3);
    dq1 = 0.5*( p*q0 + r*q2 - q*q3);
    dq2 = 0.5*( q*q0 - r*q1 + p*q3);
    dq3 = 0.5*( r*q0 + q*q1 - p*q2);
    
    p += dp*dt;
    q += dq*dt;
    r += dr*dt;
    
    q0 += dq0*dt;
    q1 += dq1*dt;
    q2 += dq2*dt;
    q3 += dq3*dt;
    
    this->defAttitude(osg::Quat(q1, q2, q3, q0));
    this->defOmega(vec3(p,q,r));
    
    _torque = vec3(0.,0.,0.);
    
}

std::string Vessel::obtNom() const {
    return _nom;
}

void Vessel::decrMass(double dm) {
    _mass -= dm;
}

vec3 Vessel::obtPosition() const {
    return _osg_node->getPosition();
}

void Vessel::defPosition(const vec3& position) {
    _osg_node->setPosition(position);
}

vec3 Vessel::obtVitesse() const {
    return _vel;
}

void Vessel::defVitesse(const vec3& vitesse) {
    _vel = vitesse;
}

osg::Quat Vessel::obtAttitude() const {
    return _osg_node->getAttitude();
}

void Vessel::defAttitude(const osg::Quat& attitude) {
    _osg_node->setAttitude(attitude);
}

vec3 Vessel::obtOmega() const {
    return _omega;
}

void Vessel::defOmega(const vec3& omega) {
    _omega = omega;
}


