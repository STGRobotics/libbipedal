#ifndef __TRAJECTORY_PLAYER_H__
#define __TRAJECTORY_PLAYER_H__

#include <MMM/Motion/Motion.h>

#include "../../bipedal.h"

class TrajectoryException : std::exception
{
public:
    TrajectoryException(const std::string& trajectoryName)
    : errorMsg("Could not find a trajectory named " + trajectoryName)
    {
    }

    virtual const char* what()
    {
        return errorMsg.c_str();
    }
private:
    std::string errorMsg;
};

/**
 * Simple playback of trajectories generated by TrajectoryExporter
 */
class TrajectoryPlayer
{
public:
    TrajectoryPlayer(const std::string& motionPath, const std::string& goalMotionName)
        : frameCounter(0)
        , isRunning(false)
    {
        if (!loadMotion(motionPath, goalMotionName))
        {
            throw TrajectoryException(goalMotionName);
        }
    }

    /**
     * This steps the internal clock.
     * Should be called by callback in fixed intervals.
     *
     * Returns true as long as the is a control trajectory.
     */
    bool update(float timestep);

    /**
     * Start control sequence.
     *
     * Note: control() is called regardless of the state of the control motion!
     */
    void start() { isRunning = true; };

    /**
     * Reset controller to initial state.
     */
    void reset();

public:
    bool isRunning;
    float time;
    int frameCounter;
    MMM::MotionPtr motion;
    MMM::MotionFramePtr nextFrame;
    MMM::MotionFramePtr currentFrame;

private:
    bool loadMotion(const std::string& motionPath, const std::string& goalMotionName);
};

typedef boost::shared_ptr<TrajectoryPlayer> TrajectoryPlayerPtr;

#endif
