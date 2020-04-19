#include <iostream>

class IVideoDriver {
public:
  virtual void play() = 0;
};

class Alsa : public IVideoDriver {
public:
  void play() { std::cout << "play use alsa" << std::endl; };
};

class Jack : public IVideoDriver {
public:
  void play() { std::cout << "play use jack" << std::endl; };
};
  
class VideoPlayer {
public:
  VideoPlayer(IVideoDriver *d = NULL) {
    if( d == NULL ) {
      mDriver = new Alsa();
    } else
      mDriver = d;
  };
  void setVideoDriver(IVideoDriver *d) { mDriver = d; };
  void play() { mDriver->play(); };

private:
  IVideoDriver* mDriver;
};

class CLIVideoPlayer : public VideoPlayer {
public:
  CLIVideoPlayer(IVideoDriver *d) : VideoPlayer(d) {};
};

class GUIVideoPlayer: public VideoPlayer {
public:
  GUIVideoPlayer(IVideoDriver* d) : VideoPlayer(d) {};
};

class WebVideoPlayer : public VideoPlayer {
public:
  WebVideoPlayer(IVideoDriver* d) : VideoPlayer(d) {};
};

int main() {
  Alsa driverA = Alsa();
  Jack driverB = Jack();
  CLIVideoPlayer player(&driverA);
  player.play();
  player.setVideoDriver(&driverB);
  player.play();
  return 0;
}
