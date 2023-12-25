#include "namespace_manager.h"

#include <memory>
#include <shared_mutex>
#include <string>
#include <vector>

#include "state_code.h"

namespace gfs {

int filemanager::tree2array(std::vector<serialFileNode> &array,
                            fileTreeNode *node) {
  auto nextnode = serialFileNode(node->isDir, node->chunks);
  if (node->isDir) {
    for (auto &child : node->children) {
      nextnode.Children[child.first] = tree2array(array, child.second.get());
    }
  }
  //将找到的尾节点加入树形队列
  array.push_back(nextnode);
  int ans = serialCt;
  serialCt++;
  return ans;
}

std::vector<serialFileNode> filemanager::Serialize() {
  std::shared_lock<std::shared_mutex> lock(root->file_tree_mutex);
  serialCt = 0;
  std::vector<serialFileNode> new_FileNode;
  tree2array(new_FileNode, root.get());
  return new_FileNode;
}

std::shared_ptr<fileTreeNode> filemanager::array2tree(
    std::vector<serialFileNode> array, int id) {
  auto node = new fileTreeNode(array[id].IsDir, array[id].Chunks);
  if (array[id].IsDir) {
    for (auto &child : array[id].Children) {
      node->children[child.first] = array2tree(array, child.second);
    }
  }
  return std::make_shared<fileTreeNode>(node);
}

void filemanager::Deserialize(std::vector<serialFileNode> array) {
  std::shared_lock<std::shared_mutex> lock(root->file_tree_mutex);
  root = array2tree(array, array.size() - 1);
}
}  // namespace gfs