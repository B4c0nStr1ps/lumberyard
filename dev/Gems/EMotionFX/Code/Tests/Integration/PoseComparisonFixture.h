/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#include <Tests/SystemComponentFixture.h>

namespace EMotionFX
{
    class Actor;
    class ActorInstance;
    class AnimGraph;
    class MotionSet;

    struct PoseComparisonFixtureParams
    {
        const char* actorFile = nullptr;
        const char* animGraphFile = nullptr;
        const char* motionSetFile = nullptr;
        const char* recordingFile = nullptr;
        PoseComparisonFixtureParams(const char* actorFile, const char* animGraphFile, const char* motionSetFile, const char* recordingFile)
            : actorFile(actorFile), animGraphFile(animGraphFile), motionSetFile(motionSetFile), recordingFile(recordingFile)
        {}
    };

    class INTEG_PoseComparisonFixture
        : public SystemComponentFixture
        , public ::testing::WithParamInterface<PoseComparisonFixtureParams>
    {
    public:
        void SetUp() override;
        void TearDown() override;

        void LoadAssets();

    protected:
        Actor* m_actor = nullptr;
        ActorInstance* m_actorInstance = nullptr;
        AnimGraph* m_animGraph = nullptr;
        MotionSet* m_motionSet = nullptr;
    };

    // This fixture exists to separate the tests that test the pose comparsion
    // functionality from the tests that use the pose comparison functionality
    // (even though it doesn't use the recording)
    class INTEG_TestPoseComparisonFixture
        : public INTEG_PoseComparisonFixture
    {
    };
}; // namespace EMotionFX
