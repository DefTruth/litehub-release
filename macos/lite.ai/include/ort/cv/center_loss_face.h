//
// Created by DefTruth on 2021/7/14.
//

#ifndef LITE_AI_ORT_CV_CENTER_LOSS_FACE_H
#define LITE_AI_ORT_CV_CENTER_LOSS_FACE_H

#include "ort/core/ort_core.h"

namespace ortcv
{
  class LITE_EXPORTS CenterLossFace : public BasicOrtHandler
  {
  public:
    explicit CenterLossFace(const std::string &_onnx_path, unsigned int _num_threads = 1) :
        BasicOrtHandler(_onnx_path, _num_threads)
    {};

    ~CenterLossFace() override = default;

  private:
    static constexpr const float mean_val = 127.5f;
    static constexpr const float scale_val = 1.f / 127.5f;

  private:
    Ort::Value transform(const cv::Mat &mat) override;

  public:
    void detect(const cv::Mat &mat, types::FaceContent &face_content);
  };
}

#endif //LITE_AI_ORT_CV_CENTER_LOSS_FACE_H
