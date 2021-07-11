//
// Created by DefTruth on 2021/7/7.
//

#ifndef LITEHUB_ORT_CV_FOCAL_ASIA_ARCFACE_H
#define LITEHUB_ORT_CV_FOCAL_ASIA_ARCFACE_H

#include "ort/core/ort_core.h"

namespace ortcv
{
  class LITEHUB_EXPORTS FocalAsiaArcFace : public BasicOrtHandler
  {
  public:
    explicit FocalAsiaArcFace(const std::string &_onnx_path, unsigned int _num_threads = 1) :
        BasicOrtHandler(_onnx_path, _num_threads)
    {};

    ~FocalAsiaArcFace() override = default;

  private:
    static constexpr const float mean_val = 127.5f;
    static constexpr const float scale_val = 1.f / 127.5f;

  private:
    Ort::Value transform(const cv::Mat &mat) override;

  public:
    void detect(const cv::Mat &mat, types::FaceContent &face_content);
  };
}

#endif //LITEHUB_ORT_CV_FOCAL_ASIA_ARCFACE_H
