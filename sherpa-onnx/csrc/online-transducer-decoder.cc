// sherpa-onnx/csrc/online-transducer-decoder.cc
//
// Copyright (c)  2023  Xiaomi Corporation

#include "sherpa-onnx/csrc/online-transducer-decoder.h"

#include <utility>
#include <vector>

#include "onnxruntime_cxx_api.h"  // NOLINT
#include "sherpa-onnx/csrc/onnx-utils.h"

namespace sherpa_onnx {

OnlineTransducerDecoderResult::OnlineTransducerDecoderResult(
    const OnlineTransducerDecoderResult &other)
    : OnlineTransducerDecoderResult() {
  *this = other;
}

OnlineTransducerDecoderResult &OnlineTransducerDecoderResult::operator=(
    const OnlineTransducerDecoderResult &other) {
  if (this == &other) {
    return *this;
  }

  tokens = other.tokens;
  num_trailing_blanks = other.num_trailing_blanks;
  num_processed_frames = other.num_processed_frames;
  num_blank_frames = other.num_blank_frames;
  silences = other.silences;
  timestamp_frames = other.timestamp_frames;
  
  Ort::AllocatorWithDefaultOptions allocator;
  if (other.decoder_out) {
    decoder_out = Clone(allocator, &other.decoder_out);
  }

  hyps = other.hyps;

  frame_offset = other.frame_offset;
  timestamps = other.timestamps;

  return *this;
}

OnlineTransducerDecoderResult::OnlineTransducerDecoderResult(
    OnlineTransducerDecoderResult &&other)
    : OnlineTransducerDecoderResult() {
  *this = std::move(other);
}

OnlineTransducerDecoderResult &OnlineTransducerDecoderResult::operator=(
    OnlineTransducerDecoderResult &&other) {
  if (this == &other) {
    return *this;
  }

  tokens = std::move(other.tokens);
  num_trailing_blanks = other.num_trailing_blanks;
  num_processed_frames = other.num_processed_frames;
  num_blank_frames = other.num_blank_frames;
 
  decoder_out = std::move(other.decoder_out);
  hyps = std::move(other.hyps);

  frame_offset = other.frame_offset;
  timestamps = std::move(other.timestamps);
  silences = std::move(other.silences);
  timestamp_frames = std::move(other.timestamp_frames);

  return *this;
}

}  // namespace sherpa_onnx
