#ifndef _TRAJECTORY_EXPORTER_H_
#define _TRAJECTORY_EXPORTER_H_

#include <sstream>
#include <Eigen/Dense>
#include <MMM/Motion/Motion.h>

#include "../Kinematics.h"
#include "../../bipedal.h"

class TrajectoryExporter
{
public:
    TrajectoryExporter(const std::string& pathToRobot,
                       const std::vector<std::string> jointNames,
                       const Eigen::MatrixXf& bodyTrajectory,
                       const Eigen::Matrix3Xf& comTrajectory,
                       const Eigen::Matrix3Xf& comVelocity,
                       const Eigen::Matrix3Xf& comAcceleration,
                       const Eigen::Matrix2Xf& computedZMPTrajectory,
                       const Eigen::Matrix2Xf& referenceZMPTrajectory,
                       const std::vector<Eigen::Matrix4f>& leftFootTrajectory,
                       const std::vector<Eigen::Matrix4f>& rightFootTrajectory,
                       const std::vector<Eigen::Matrix4f>& chestTrajectory,
                       const std::vector<Eigen::Matrix4f>& pelvisTrajectory,
                       const std::vector<Kinematics::SupportPhase>& phase,
                       float timestep)
        : pathToRobot(pathToRobot)
        , jointNames(jointNames)
        , bodyTrajectory(bodyTrajectory)
        , comTrajectory(comTrajectory)
        , comVelocity(comVelocity)
        , comAcceleration(comAcceleration)
        , computedZMPTrajectory(computedZMPTrajectory)
        , referenceZMPTrajectory(referenceZMPTrajectory)
        , leftFootTrajectory(leftFootTrajectory)
        , rightFootTrajectory(rightFootTrajectory)
        , chestTrajectory(chestTrajectory)
        , pelvisTrajectory(pelvisTrajectory)
        , timestep(timestep)
        , phase(phase)
    {
    }

    void exportToMMM(const std::string& path);

private:

    const std::vector<std::string> jointNames;
    const Eigen::MatrixXf& bodyTrajectory;
    const Eigen::Matrix3Xf& comTrajectory;
    const Eigen::Matrix3Xf& comVelocity;
    const Eigen::Matrix3Xf& comAcceleration;
    const Eigen::Matrix2Xf& computedZMPTrajectory;
    const Eigen::Matrix2Xf& referenceZMPTrajectory;
    const std::string& pathToRobot;
    const std::vector<Eigen::Matrix4f>& leftFootTrajectory;
    const std::vector<Eigen::Matrix4f>& rightFootTrajectory;
    const std::vector<Eigen::Matrix4f>& chestTrajectory;
    const std::vector<Eigen::Matrix4f>& pelvisTrajectory;
    const std::vector<Kinematics::SupportPhase>& phase;
    float timestep;
};

#endif
