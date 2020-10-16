/*
 * Copyright 2016 Louise Poubel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
#ifndef SIMSLIDES_COMMON_HH_
#define SIMSLIDES_COMMON_HH_

#include <memory>
#include <string>

#include "Keyframe.hh"

namespace simslides
{
  class Common
  {
     /// \brief Private constructor
     private: Common() = default;

     /// \brief Get the instance
     /// \return Singleton
     public: static Common *Instance()
     {
       if (nullptr == instance)
         instance = new Common;
       return instance;
     }

     public: std::function<void(const ignition::math::Pose3d &)> moveCamera;
     public: std::function<void(const std::string &, bool)> setVisualVisible;
     public: std::function<void(std::chrono::steady_clock::duration)> seekLog;
     public: std::function<ignition::math::Pose3d()> initialCameraPose;
     public: std::function<ignition::math::Pose3d(const std::string &)>
         visualPose;

     /// \brief Static instance
     static Common *instance;
  };


  /// \brief Prefix for slide models' names, used for creating model files
  /// and to find slides during presentation.
  /// TODO(louise) Deprecate slide prefix from ImportDialog
  extern std::string slidePrefix;

  /// \brief Path where to save / find slide models
  extern std::string slidePath;

  /// \brief Vector of keyframes loaded for presentation
  extern std::vector<Keyframe *> keyframes;

  /// \brief User camera far clip as set by the user.
  extern double farClip;

  /// \brief User camera near clip as set by the user.
  extern double nearClip;

  /// \brief Keep track of current keyframe index.
  /// -1 means the "home" camera pose.
  /// 0 is the first keyframe.
  extern int currentKeyframe;

  /// \brief Total number of keyframes.
  /// -1 means not presenting.
  extern int slideCount;

  extern const double kEyeOffsetX;
  extern const double kEyeOffsetY;
  extern const double kEyeOffsetZ;
  extern const double kEyeOffsetRoll;
  extern const double kEyeOffsetPitch;
  extern const double kEyeOffsetYaw;

  /// \brief Load <gui><plugin> tag for libsimslides.
  /// \param[in] _sdf SDF element.
  void LoadPluginSDF(const sdf::ElementPtr _sdf);

  /// \brief Handle an incoming key press from the user
  /// \param[in] _key Key as an integer
  void HandleKeyPress(int _key);

  /// \brief Change to the given keyframe.
  /// If -1, go back to initial pose.
  /// If larger than total of keyframes, go to last keyframe.
  /// \param[in] _keyframe Index of keyframe to go to.
  void ChangeKeyframe(int _keyframe);
}

#endif
