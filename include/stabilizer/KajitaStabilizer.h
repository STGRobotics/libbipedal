#ifndef __KAJITA_STABILIZER_H__
#define __KAJITA_STABILIZER_H__

#include <SimDynamics/SimDynamics.h>
#include <SimDynamics/DynamicsEngine/DynamicsRobot.h>
#include <VirtualRobot/VirtualRobot.h>

#include <boost/shared_ptr.hpp>
#include <string>

#include "../bipedal.h"

#include "kajita/ForceDistributor.h"

class FootForceController;
class FootTorqueController;
class ChestPostureController;

typedef boost::shared_ptr<FootForceController> FootForceControllerPtr;
typedef boost::shared_ptr<FootTorqueController> FootTorqueControllerPtr;
typedef boost::shared_ptr<ChestPostureController> ChestPostureControllerPtr;

class KajitaStabilizer
{
public:

    VirtualRobot::RobotPtr getInvertedRobot();

    KajitaStabilizer(const VirtualRobot::RobotPtr& robot,
                     const VirtualRobot::ForceTorqueSensorPtr& leftAnkleSensorX,
                     const VirtualRobot::ForceTorqueSensorPtr& rightAnkleSensorX,
                     const VirtualRobot::ForceTorqueSensorPtr& leftAnkleSensorY,
                     const VirtualRobot::ForceTorqueSensorPtr& rightAnkleSensorY);

    const Eigen::Matrix4f& getChestPoseRef() { return chestPoseRef; }
    const Eigen::Matrix4f& getPelvisPoseRef() { return pelvisPoseRef; }
    const Eigen::Matrix4f& getLeftFootPoseRef() { return leftFootPoseRef; }
    const Eigen::Matrix4f& getRightFootPoseRef() { return rightFootPoseRef; }
    const Eigen::Vector3f& getCoMPositionRef() { return comPositionRef; }
    const Eigen::Vector3f& getZMPPositionRef() { return zmpPositionRef; }

    const Eigen::Matrix4f& getChestPose() { return chestPose; }
    const Eigen::Matrix4f& getPelvisPose() { return pelvisPose; }
    const Eigen::Matrix4f& getLeftFootPose() { return leftFootPose; }
    const Eigen::Matrix4f& getRightFootPose() { return rightFootPose; }

    const DampeningController& getLeftAnkleTorqueXController();
    const DampeningController& getLeftAnkleTorqueYController();
    const DampeningController& getRightAnkleTorqueXController();
    const DampeningController& getRightAnkleTorqueYController();
    const DampeningController& getPelvisController();

    const Eigen::Vector3f& getLeftAnkleTorque() { return ft.leftTorque;}
    const Eigen::Vector3f& getRightAnkleTorque() { return ft.rightTorque;}
    const Eigen::Vector3f& getLeftAnkleForce() { return ft.leftForce;}
    const Eigen::Vector3f& getRightAnkleForce() { return ft.rightForce;}

    const Eigen::VectorXf& getResultAngles() { return resultAngles; }
    const VirtualRobot::RobotNodeSetPtr& getNodes() { return nodes; }

    void update(float dt,
                Kinematics::SupportPhase phase,
                const Eigen::Vector3f& zmp,
                const Eigen::Matrix4f& chestPoseRef,
                const Eigen::Matrix4f& pelvisPoseRef,
                const Eigen::Matrix4f& leftFootPoseRef,
                const Eigen::Matrix4f& rightFootPoseRef,
                const Eigen::Vector3f& comPositionRef);

private:
    void adaptFrame(Eigen::Matrix4f& frame);

    // needs to be affected by torso rotation + orientation
    VirtualRobot::RobotNodePtr chest;
    // should not be affected by torso rotation + orientation, only changes in leg angles
    VirtualRobot::RobotNodePtr pelvis;
    // joint + body of left foot
    VirtualRobot::RobotNodePtr leftFootBody;
    // joint + body of right foot
    VirtualRobot::RobotNodePtr rightFootBody;
    // joint + body of left ankle
    VirtualRobot::RobotNodePtr leftAnkleBody;
    // joint + body of right ankle
    VirtualRobot::RobotNodePtr rightAnkleBody;
    // TCP on left foot
    VirtualRobot::RobotNodePtr leftFoot;
    // TCP on right foot
    VirtualRobot::RobotNodePtr rightFoot;
    // all nodes that are used for the IK
    VirtualRobot::RobotNodeSetPtr nodes;

    FootForceControllerPtr             footForceController;
    FootTorqueControllerPtr            footTorqueController;
    ChestPostureControllerPtr          chestPostureController;
    ForceDistributorPtr                forceDistributor;
    VirtualRobot::ForceTorqueSensorPtr leftAnkleSensorX;
    VirtualRobot::ForceTorqueSensorPtr rightAnkleSensorX;
    VirtualRobot::ForceTorqueSensorPtr leftAnkleSensorY;
    VirtualRobot::ForceTorqueSensorPtr rightAnkleSensorY;
    ReferenceIKPtr                     referenceIK;

    std::vector<VirtualRobot::RobotNodePtr> trajectoryNodes;

    Eigen::Matrix4f chestPoseRef;
    Eigen::Matrix4f pelvisPoseRef;
    Eigen::Matrix4f leftFootPoseRef;
    Eigen::Matrix4f rightFootPoseRef;
    Eigen::Vector3f comPositionRef;
    Eigen::Vector3f zmpPositionRef;

    Eigen::Matrix4f chestPose;
    Eigen::Matrix4f pelvisPose;
    Eigen::Matrix4f leftFootPose;
    Eigen::Matrix4f rightFootPose;
    Eigen::Vector3f comPosition;
    Eigen::Vector3f zmpPosition;

    Eigen::Matrix4f stepAdaptionFrame;

    Eigen::Matrix4f rootPose;
    Eigen::VectorXf resultAngles;
    ForceDistributor::ForceTorque ft;
};


#endif
