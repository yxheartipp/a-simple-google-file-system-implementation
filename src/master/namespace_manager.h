#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "state_code.h"

namespace gfs {
struct fileTreeNode;
typedef std::shared_ptr<fileTreeNode> fileTreeNodePtr;

struct fileTreeNode {
  std::mutex file_tree_mutex;

  bool isDir;
  std::map<std::string, fileTreeNodePtr> children;

  uint64_t length;  //文件大小
  uint64_t chunks;  //包含chunk数量
};

class serialFileNode {
 public:
  bool IsDir;
  std::map<std::string, int> Children;
  uint64_t Chunks;
};

class filemanager {
 public:
  std::vector<fileTreeNodePtr> root;

 public:
  filemanager();
  ~filemanager() = default;
  int tree2array(std::vector<serialFileNode>& array, fileTreeNode* node);

  std::vector<serialFileNode> Serialize();

  fileTreeNodePtr array2tree(std::vector<serialFileNode> array, int id);

  bool Deserialize(std::vector<serialFileNode> array);

  status_code lockParents(std::string path, bool goDown);

  status_code UnlockParents(std::vector<std::string>);

  std::vector<std::string> PartionLastName(std::string path);

  status_code Create(std::string path);

  status_code Delete(std::string path);

  status_code Rename(std::string source, std::string target);

  status_code Mkdir(std::string path);

  std::vector<PathInfo> List(std::string path);

 private:
  int serialCt;
};
}  // namespace gfs