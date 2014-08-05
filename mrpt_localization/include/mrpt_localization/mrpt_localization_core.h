/***********************************************************************************
 * Revised BSD License                                                             *
 * Copyright (c) 2014, Markus Bader <markus.bader@tuwien.ac.at>                    *
 * All rights reserved.                                                            *
 *                                                                                 *
 * Redistribution and use in source and binary forms, with or without              *
 * modification, are permitted provided that the following conditions are met:     *
 *     * Redistributions of source code must retain the above copyright            *
 *       notice, this list of conditions and the following disclaimer.             *
 *     * Redistributions in binary form must reproduce the above copyright         *
 *       notice, this list of conditions and the following disclaimer in the       *
 *       documentation and/or other materials provided with the distribution.      *
 *     * Neither the name of the Vienna University of Technology nor the           *
 *       names of its contributors may be used to endorse or promote products      *
 *       derived from this software without specific prior written permission.     *
 *                                                                                 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND *
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED   *
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE          *
 * DISCLAIMED. IN NO EVENT SHALL Markus Bader BE LIABLE FOR ANY                    *
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES      *
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;    *
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND     *
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT      *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS   *
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                    *                       *
 ***********************************************************************************/

#ifndef MRPT_LOCALIZATION_CORE_H
#define MRPT_LOCALIZATION_CORE_H

#include <iostream>
#include <stdint.h>

#include <mrpt/bayes/CParticleFilter.h>
#include <mrpt/slam/CActionRobotMovement2D.h>
#include <mrpt/slam/CMultiMetricMap.h>
#include <mrpt/poses/CPose2D.h>
#include <mrpt/poses/CPosePDFGaussian.h>
#include <mrpt/utils/CTicTac.h>

#include <mrpt_bridge/mrpt_log_macros.h>

#include <mrpt/slam/CMultiMetricMap.h>
#include <mrpt/slam/CActionCollection.h>
#include <mrpt/slam/CMonteCarloLocalization2D.h>
#include <mrpt/slam/CObservationOdometry.h>
#include <mrpt/slam/CSensoryFrame.h>
#include <mrpt/utils/CTicTac.h>
#include <mrpt/poses/CPose2D.h>

class PFLocalizationCore {
  MRPT_VIRTUAL_LOG_MACROS;
public:
    enum PFStates {NA, INIT, RUN} ;
    PFLocalizationCore ();
    ~PFLocalizationCore();
    void init();
protected:
    mrpt::slam::CActionRobotMovement2D::TMotionModelOptions odom_params_dummy_;
    mrpt::slam::CActionRobotMovement2D::TMotionModelOptions odom_params_;
    mrpt::slam::CMultiMetricMap metric_map_;
    mrpt::slam::CMonteCarloLocalization2D  pdf_;
    mrpt::bayes::CParticleFilter pf_;
    mrpt::bayes::CParticleFilter::TParticleFilterStats   pf_stats_;
    mrpt::poses::CPosePDFGaussian initialPose_;
    mrpt::system::TTimeStamp timeLastUpdate_;
    mrpt::utils::CTicTac tictac_;
    size_t update_counter_;
    PFStates state_;
    mrpt::poses::CPose2D odomLastObservation_;

    int initialParticleCount_;
    void initializeFilter(mrpt::utils::CPosePDFGaussian &p);
    void observation(mrpt::slam::CSensoryFramePtr _sf, mrpt::slam::CObservationOdometryPtr _odometry);
    void updateFilter(mrpt::slam::CActionCollectionPtr _action, mrpt::slam::CSensoryFramePtr _sf);
};

#endif // MRPT_LOCALIZATION_CORE_H
