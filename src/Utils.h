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
};

#endif
