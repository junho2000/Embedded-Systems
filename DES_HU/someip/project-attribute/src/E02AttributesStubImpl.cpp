// Copyright (C) 2014-2019 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "E02AttributesStubImpl.hpp"

E02AttributesStubImpl::E02AttributesStubImpl() {
    cnt = 3;
}

E02AttributesStubImpl::~E02AttributesStubImpl() {
}

void E02AttributesStubImpl::incCounter() {
    // cnt++;
    // setXAttribute((int32_t)cnt);
    std::cout << "Service get callback value: " << getXAttribute() << std::endl;
    std::cout <<  "New counter value = " << cnt << "!" << std::endl;
}
