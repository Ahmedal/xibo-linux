#include "Media.hpp"

#include "wrapper/GstFwd.hpp"
#include <spdlog/spdlog.h>

class Audio : public Media
{
public:
    Audio(int id, int duration, const std::string& uri, bool muted, bool looped, double volume);
    ~Audio() override;

    void stop() override;
    void start() override;
    void startTimer() override;
    Gtk::Widget& handler() override { }

    bool muted() const;
    bool looped() const;
    double volume() const;

    void apply(MediaVisitor& visitor) override;
private:
    bool busMessageWatch(const Gst::RefPtr<Gst::Message>& message);
    void noMorePads();
    void onPadAdded(const Gst::RefPtr<Gst::Pad>& pad);
    void setVolume(double volume);
    void play();

private:
    bool m_muted;
    bool m_looped;

    bool m_audioEnded = false;
    std::shared_ptr<spdlog::logger> m_logger;

    Gst::RefPtr<Gst::Pipeline> m_pipeline;
    Gst::RefPtr<Gst::FileSrc> m_source;
    Gst::RefPtr<Gst::Decodebin> m_decodebin;
    Gst::RefPtr<Gst::Volume> m_volume;
    Gst::RefPtr<Gst::AudioConvert> m_audioConverter;
    Gst::RefPtr<Gst::AutoAudioSink> m_audioSink;
};
