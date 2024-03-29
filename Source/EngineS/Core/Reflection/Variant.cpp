#include "Variant.hpp"

namespace EngineS {

Variant::Variant() : _handler(new Detail::VariantHandlerEmpty {}) {}

Variant::~Variant() {
    if (_handler)
        _handler->Destroy(_data);
}

Variant::Variant(const Variant& other) : _handler(other._handler->Clone()) {
    _data = _handler->Copy(other._data);
}

Variant::Variant(Variant&& other) noexcept : _data(), _handler(nullptr) {
    std::swap(_handler, other._handler);
    std::swap(_data, other._data);
}

Variant& Variant::operator=(const Variant& other) {
    if (this == &other)
        return *this;

    _handler->Destroy(_data);
    _data    = other._data;
    _handler = other._handler->Clone();
    return *this;
}

Variant& Variant::operator=(Variant&& other) noexcept {
    std::swap(_data, other._data);
    _handler = std::move(other._handler);

    return *this;
}

bool Variant::IsValid() const {
    return _handler && _handler->IsValid();
}

Detail::VariantHandlerBase* Variant::GetHandler() const {
    return _handler.get();
}

void* Variant::GetRawAddress() const {
    return _handler->GetRawAddress(_data);
}

const Type* Variant::GetType() const {
    return _handler->GetType();
}

int Variant::GetInt() const {
    return ToNumber<int>();
}

float Variant::GetFloat() const {
    return ToNumber<float>();
}

double Variant::GetDouble() const {
    return ToNumber<double>();
}

} // namespace EngineS