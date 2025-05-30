// Copyright (c), ETH Zurich and UNC Chapel Hill.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
//     * Neither the name of ETH Zurich and UNC Chapel Hill nor the names of
//       its contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include "colmap/scene/reconstruction.h"

#include <functional>
#include <unordered_map>
#include <vector>

namespace colmap {

// Helper method to extract sorted camera, image, point3D identifiers.
// We sort the identifiers before writing to the stream, such that we produce
// deterministic output independent of standard library dependent ordering of
// the unordered map container.
template <typename ID_TYPE, typename DATA_TYPE>
std::vector<ID_TYPE> ExtractSortedIds(
    const std::unordered_map<ID_TYPE, DATA_TYPE>& data,
    const std::function<bool(const DATA_TYPE&)>& filter = nullptr) {
  std::vector<ID_TYPE> ids;
  ids.reserve(data.size());
  for (const auto& [id, d] : data) {
    if (filter == nullptr || filter(d)) {
      ids.push_back(id);
    }
  }
  std::sort(ids.begin(), ids.end());
  return ids;
}

void CreateOneRigPerCamera(Reconstruction& reconstruction);

void CreateFrameForImage(const Image& image,
                         const Rigid3d& cam_from_world,
                         Reconstruction& reconstruction);

std::unordered_map<image_t, Frame*> ExtractImageToFramePtr(
    Reconstruction& reconstruction);

}  // namespace colmap
