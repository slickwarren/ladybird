/*
 * Copyright (c) 2023, Andrew Kaster <akaster@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibGfx/Rect.h>
#include <LibWeb/Page/Page.h>
#include <LibWeb/PixelUnits.h>
#include <WebWorker/Forward.h>

namespace WebWorker {

class PageHost final : public Web::PageClient {
    GC_CELL(PageHost, Web::PageClient);
    GC_DECLARE_ALLOCATOR(PageHost);

public:
    static GC::Ref<PageHost> create(JS::VM& vm, ConnectionFromClient& client);

    virtual ~PageHost();

    virtual Web::Page& page() override;
    virtual Web::Page const& page() const override;
    virtual bool is_connection_open() const override;
    virtual Gfx::Palette palette() const override;
    virtual Web::DevicePixelRect screen_rect() const override;
    virtual double device_pixels_per_css_pixel() const override;
    virtual Web::CSS::PreferredColorScheme preferred_color_scheme() const override;
    virtual Web::CSS::PreferredContrast preferred_contrast() const override;
    virtual Web::CSS::PreferredMotion preferred_motion() const override;
    virtual void paint_next_frame() override { }
    virtual void process_screenshot_requests() override { }
    virtual void start_display_list_rendering(Web::DevicePixelRect const&, Web::Painting::BackingStore&, Web::PaintOptions, Function<void()>&& callback) override;
    virtual void request_file(Web::FileRequest) override;
    virtual bool is_ready_to_paint() const override { return true; }
    virtual Web::DisplayListPlayerType display_list_player_type() const override { VERIFY_NOT_REACHED(); }
    virtual bool is_headless() const override { VERIFY_NOT_REACHED(); }
    virtual Queue<Web::QueuedInputEvent>& input_event_queue() override { VERIFY_NOT_REACHED(); }
    virtual void report_finished_handling_input_event([[maybe_unused]] u64 page_id, [[maybe_unused]] Web::EventResult event_was_handled) override { VERIFY_NOT_REACHED(); }

private:
    explicit PageHost(ConnectionFromClient&);
    virtual void visit_edges(JS::Cell::Visitor&) override;

    void setup_palette();

    ConnectionFromClient& m_client;
    GC::Ref<Web::Page> m_page;
    RefPtr<Gfx::PaletteImpl> m_palette_impl;
};

}
