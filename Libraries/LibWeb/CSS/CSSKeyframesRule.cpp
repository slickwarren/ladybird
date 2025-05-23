/*
 * Copyright (c) 2023, Ali Mohammad Pur <mpfard@serenityos.org>
 * Copyright (c) 2024, Andreas Kling <andreas@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/CSSKeyframesRulePrototype.h>
#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/CSS/CSSKeyframesRule.h>
#include <LibWeb/CSS/CSSRuleList.h>

namespace Web::CSS {

GC_DEFINE_ALLOCATOR(CSSKeyframesRule);

GC::Ref<CSSKeyframesRule> CSSKeyframesRule::create(JS::Realm& realm, FlyString name, GC::Ref<CSSRuleList> css_rules)
{
    return realm.create<CSSKeyframesRule>(realm, move(name), move(css_rules));
}

CSSKeyframesRule::CSSKeyframesRule(JS::Realm& realm, FlyString name, GC::Ref<CSSRuleList> keyframes)
    : CSSRule(realm, Type::Keyframes)
    , m_name(move(name))
    , m_rules(move(keyframes))
{
    for (auto& rule : *m_rules)
        rule->set_parent_rule(this);
}

void CSSKeyframesRule::visit_edges(Visitor& visitor)
{
    Base::visit_edges(visitor);
    visitor.visit(m_rules);
}

void CSSKeyframesRule::initialize(JS::Realm& realm)
{
    WEB_SET_PROTOTYPE_FOR_INTERFACE(CSSKeyframesRule);
    Base::initialize(realm);
}

String CSSKeyframesRule::serialized() const
{
    StringBuilder builder;
    builder.appendff("@keyframes \"{}\"", name());
    builder.append(" { "sv);
    for (auto const& keyframe : *m_rules) {
        builder.append(keyframe->css_text());
        builder.append(' ');
    }
    builder.append('}');
    return MUST(builder.to_string());
}

WebIDL::UnsignedLong CSSKeyframesRule::length() const
{
    return m_rules->length();
}

}
