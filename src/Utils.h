#ifndef MADCAM_UTILS_H
#define MADCAM_UTILS_H

enum Layout {
  SINGLE,
  DUAL_HORIZ,
  TRIPLE_HORIZ,
  TILED,
  MONOCLE
};

enum ViewMode {
  CROP, SCALE
};

struct Scene {
  enum Layout   layout;
  enum ViewMode viewMode;
  bool          triggerMode;
  int           fx;
  int           amountX;
  int           amountY;
  vector<int>   slots;
  bool          feedbackMode;
  int           alpha;
  int           xoffset;
  int           yoffset;
  int           iterations;
};

struct Config {
  vector<tuple<string,int>> camMap;
  vector<tuple<int,int>> noteMap;
  vector<Scene> sceneMap;
};

#endif
