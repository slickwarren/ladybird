/*
 * Copyright (c) 2020, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/Assertions.h>
#include <LibWeb/Bindings/HTMLModElementPrototype.h>
#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/HTML/HTMLModElement.h>

namespace Web::HTML {

GC_DEFINE_ALLOCATOR(HTMLModElement);

HTMLModElement::HTMLModElement(DOM::Document& document, DOM::QualifiedName qualified_name)
    : HTMLElement(document, move(qualified_name))
{
}

HTMLModElement::~HTMLModElement() = default;

void HTMLModElement::initialize(JS::Realm& realm)
{
    WEB_SET_PROTOTYPE_FOR_INTERFACE(HTMLModElement);
    Base::initialize(realm);
}

Optional<ARIA::Role> HTMLModElement::default_role() const
{
    // https://www.w3.org/TR/html-aria/#el-del
    if (local_name() == TagNames::del)
        return ARIA::Role::deletion;
    // https://www.w3.org/TR/html-aria/#el-ins
    if (local_name() == TagNames::ins)
        return ARIA::Role::insertion;
    VERIFY_NOT_REACHED();
}

}
