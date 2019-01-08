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
  std::vector<int>   slots;
  bool          feedbackMode;
  int           alpha;
  int           xoffset;
  int           yoffset;
  int           iterations;
};

struct Config {
	std::vector<std::tuple<std::string,int>> camMap;
  	std::vector<std::tuple<int,int>> noteMap;
  	std::vector<Scene> sceneMap;
};

#endif
