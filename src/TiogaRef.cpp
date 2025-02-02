
#include "TiogaRef.h"
#include "tioga.h"
#include <iostream>

namespace tioga_nalu {

TiogaRef& TiogaRef::self(TIOGA::tioga* tg)
{
    static bool initialized{false};
    static std::unique_ptr<TiogaRef> tgref;

    if (initialized) {
        if (tg != nullptr)
            throw std::runtime_error(
                "Multiple registration of TIOGA object encountered");
    } else {
        if (tg == nullptr) {
            tgref.reset(new TiogaRef());
        } else {
            tgref.reset(new TiogaRef(tg));
        }
        initialized = true;
    }

    return *tgref;
}

TiogaRef::TiogaRef() : tg_(new TIOGA::tioga()), owned_(true) {}

TiogaRef::TiogaRef(TIOGA::tioga* tg) : tg_(tg), owned_(false) {}

TiogaRef::~TiogaRef()
{
    if (owned_ && (tg_ != nullptr)) {
        delete tg_;
        tg_ = nullptr;
    }
}

} // namespace tioga_nalu
