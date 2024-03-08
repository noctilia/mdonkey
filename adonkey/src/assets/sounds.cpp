#include <SFML/Audio.hpp>

#include <array>
#include <string>
#include <sstream>
#include <cassert>

#include <algorithm>
#include "sounds.hpp"
#include "../core/log.hpp"


namespace
{
  /** internal store of all loaded sound effects. */
  std::array<sf::SoundBuffer, SND_COUNT> audio_samples;
  std::array<sf::Sound, SND_COUNT> audio_sound;

  std::array<const char*, SND_COUNT> snd_filenames {
    "music_1.wav",
    "music_2.wav",
    "music_hammer.wav",
    "death.wav",
    "smash.wav",
    "how_high.wav",
    "intro.wav",
    "jump.wav",
    "score.wav",
    "run.wav",
    "fall.wav",
    "win_1.wav",
    "win_2.wav",
    "win_level.wav",
    "spring_bounce.wav",
    "spring_fall.wav",
    "oil_light.wav",
    "boot.wav",
    "countdown.wav",
  };

  const std::string snd_path {"assets/snd/"};
}

bool load_sounds()
{
  log(log_lvl::info, "loading sounds");

  auto log_loading = [](const char* snd_filename){
    std::stringstream ss{};
    ss << "loading sound '" << fmt_bold << snd_filename << fmt_clear << "'.";
    log(log_lvl::info, ss.str());
  };

  auto log_load_fail = [](const char* snd_filename) {
    std::stringstream ss{};
    ss << "failed to load sound '" << fmt_bold << snd_filename << fmt_clear << "'.";
    log(log_lvl::fatal, ss.str());
  };

  for(auto snd = 0; snd < SND_COUNT; ++snd){
    log_loading(snd_filenames[snd]);
    bool rc = audio_samples[snd].loadFromFile((snd_path + snd_filenames[snd]).c_str());
    if(!rc){
      log_load_fail(snd_filenames[snd]);
      return false;
    }
  }

  return true;
}

void unload_sounds()
{
  log(log_lvl::info, "unloading sounds");
  //for(auto sample : audio_samples){
  //  al_destroy_sample(sample);
  //}
}

snd_play_id play_sound(sound_id snd, float speed, bool loop, float gain)
{
  //assert(0 <= snd && snd < SND_COUNT);
  //ALLEGRO_SAMPLE_ID sample_id;
  //ALLEGRO_PLAYMODE mode = loop ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE;
  //speed = std::clamp(speed, 0.f, 1.f);
  //if(!al_play_sample(audio_samples[snd], gain, 0.f, speed, mode, &sample_id)) 
  //  return {};

  ALLEGRO_SAMPLE_ID sample_id;

  // TODO: check if sound is already playing and stop it.
  // TODO: set sound buffer on initialization.?
  audio_sound[snd].setBuffer(audio_samples[snd]);
  audio_sound[snd].play();

  return sample_id;
}

void stop_sound(snd_play_id id)
{
  if(!id.has_value()) 
    return;
  //al_stop_sample(&id.value());
  audio_sound[id.value()].stop(); 
}
