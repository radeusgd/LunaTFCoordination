//
// Created by mateusz on 01.12.18.
//

#include "tensors.h"
#include "../tensor/Tensor.h"
#include "../helpers/LifeTimeManager.h"

#include <vector>
#include <memory>

Tensor<TF_FLOAT> *make_float_tensor(float const* array, int64_t len)
{
	auto tensor_ptr = std::make_shared<Tensor<TF_FLOAT>>(array, len);

	return LifetimeManager::instance().addOwnership(std::move(tensor_ptr));
}

Tensor<TF_FLOAT> *make_float_tensor_arr(float const** array, int64_t width, int64_t height)
{
	auto tensor_ptr = std::make_shared<Tensor<TF_FLOAT>>(array, width, height);

	return LifetimeManager::instance().addOwnership(std::move(tensor_ptr));
}

Tensor<TF_INT32> *make_int_tensor(const int32_t* array, int64_t len)
{
	auto tensor_ptr = std::make_shared<Tensor<TF_INT32>>(array, len);

	return LifetimeManager::instance().addOwnership(std::move(tensor_ptr));
}

float get_tensor1d_float_value_at(Tensor<TF_FLOAT> *tensor, int64_t idx)
{
	return get_tensor_float_value_at(tensor, &idx, 1);
}

float get_tensor_float_value_at(Tensor<TF_FLOAT> *tensor, int64_t *idxs, size_t len)
{
	return LifetimeManager::instance().accessOwned(tensor)->at(idxs, len);
}

int32_t get_tensor1d_int_value_at(Tensor<TF_INT32> *tensor, int64_t idx)
{
	return get_tensor_int_value_at(tensor, &idx, 1);
}

int32_t get_tensor_int_value_at(Tensor<TF_INT32> *tensor, int64_t *idxs, size_t len)
{
	return LifetimeManager::instance().accessOwned(tensor)->at(idxs, len);
}

int64_t tensor_float_length(Tensor<TF_FLOAT> * tensor) {
	return LifetimeManager::instance().accessOwned(tensor)->shape()[0];
}