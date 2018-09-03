/**
 * Copyright © 2018 IBM Corporation
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

#include "argument.hpp"

#include <iostream>
#include <string>

static void ExitWithError(const char* err, char** argv)
{
    phosphor::certs::util::ArgumentParser::usage(argv);
    std::cerr << std::endl;
    std::cerr << "ERROR: " << err << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
    // Read arguments.
    auto options = phosphor::certs::util::ArgumentParser(argc, argv);

    // Parse arguments
    auto type = std::move((options)["type"]);
    if (type == phosphor::certs::util::ArgumentParser::empty_string)
    {
        ExitWithError("type not specified.", argv);
    }

    auto endpoint = std::move((options)["endpoint"]);
    if (endpoint == phosphor::certs::util::ArgumentParser::empty_string)
    {
        ExitWithError("endpoint not specified.", argv);
    }

    auto path = std::move((options)["path"]);
    if (path == phosphor::certs::util::ArgumentParser::empty_string)
    {
        ExitWithError("path not specified.", argv);
    }

    // unit is an optional parametr
    auto unit = std::move((options)["unit"]);

    return 0;
}