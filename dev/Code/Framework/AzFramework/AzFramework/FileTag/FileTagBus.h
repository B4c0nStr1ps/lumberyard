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

#pragma once

#include <AzCore/EBus/EBus.h>
#include <AzCore/std/string/string.h>
#include <AzCore/std/containers/set.h>
#include <AzCore/Outcome/Outcome.h>
#include <AzFramework/Asset/FileTagAsset.h>

namespace AzFramework
{
    namespace FileTag
    {
        enum FileTagType: int 
        {
            WhiteList = 0, 
            BlackList
        };


        /**
        * Event bus for adding/removing file tags.
        */
        class FileTagsEvent
            : public AZ::EBusTraits
        {
        public:

            //////////////////////////////////////////////////////////////////////////
            static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
            /////////////////////////////////////////////////////////////////////////

            ///! Saves the corresponding fileTagType file to disk.
            ///! destinationFilePath param is optional, the app root path for the application will be
            ///! used as the destination directory, if it is not specified by the user.
            virtual bool Save(FileTagType /*fileTagType*/, const AZStd::string& /*destinationFilePath*/) = 0;

            ///! Add file tags based on a filepath.
            virtual AZ::Outcome<AZStd::string, AZStd::string> AddFileTags(const AZStd::string& /*filePath*/, FileTagType /*fileTagType*/, const AZStd::vector<AZStd::string>& /*fileTags*/) = 0;

            ///! Remove file tags based on a filepath.
            virtual AZ::Outcome<AZStd::string, AZStd::string> RemoveFileTags(const AZStd::string& /*filePath*/, FileTagType /*fileTagType*/, const AZStd::vector<AZStd::string>& /*fileTags*/) = 0;

            ///! Add tags based on filepattern.
            ///! Pattern can either be a wildcard or a regex.
            virtual AZ::Outcome<AZStd::string, AZStd::string> AddFilePatternTags(const AZStd::string& /*pattern*/, AzFramework::FileTag::FilePatternType /*filePatternType*/, FileTagType /*fileTagType*/, const AZStd::vector<AZStd::string>& /*fileTags*/) = 0;

            ///! Remove tags based on filepattern.
            virtual AZ::Outcome<AZStd::string, AZStd::string> RemoveFilePatternTags(const AZStd::string& /*pattern*/, AzFramework::FileTag::FilePatternType /*filePatternType*/, FileTagType /*fileTagType*/, const AZStd::vector<AZStd::string>& /*fileTags*/) = 0;
        };

        using FileTagsEventBus = AZ::EBus<FileTagsEvent>;

        /**
        * Event bus for querying file tags.
        */
        class QueryFileTagsEvent
            : public AZ::EBusTraits
        {
        public:
            //////////////////////////////////////////////////////////////////////////
            static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::ById;
            using BusIdType = int; // Type is AzFramework::FileTag::FileTagType - Cast to int from enum not supported by vs2015 compiler
            //////////////////////////////////////////////////////////////////////////
            ///! Loads the corresponding file for the tags type specified.
            ///! filePath param is optional and if not specified than the app root path for the application
            ///! will be searched for tags type file specified.
            virtual bool Load(const AZStd::string& /*filePath*/) = 0;

            ///! Load engine dependencies specified inside the *_dependencies.xml
            virtual bool LoadEngineDependencies(const AZStd::string& filePath) = 0;

            ///! Given a filepath and a list of file tags, return true if all of those tags are on it, otherwise return false.
            ///! Please note that we will be doing a case insensitive match and therefore we are taking fileTags param by value. 
            virtual bool Match(const AZStd::string& /*filePath*/, AZStd::vector<AZStd::string> /*fileTags*/) = 0;

            ///! Given a filepath, returns all of the tags that are on it.
            virtual AZStd::set<AZStd::string> GetTags(const AZStd::string& /*filePath*/) = 0;
        };

        using QueryFileTagsEventBus = AZ::EBus<QueryFileTagsEvent>;
    }

} // AzFramework
