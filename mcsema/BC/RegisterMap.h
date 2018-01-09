// RegisterMap, handles reflection on State structure
// to access registers based on offsets, get names, etc

#include <string>

#include <llvm/IR/DerivedTypes.h>

namespace mcsema {

// what is the scope for this class?
struct Register {
  std::string name;
  size_t size;
  Register(size_t size_, llvm::Type *typehint) : size(size_) { }
};
  
// TODO: Ask Peter his thoughts on this design
// depending on how efficient we want this to be
// we'll have to make some changes
class RegisterMap {

  struct RegisterGroup {
    std::string name;
    std::vector<Register *> members;
    RegisterGroup(std::string name_) : name(name_) {}
    void addRegister(Register *r) { members.push_back(r); }
  };

  std::vector<Register *> _registers;

  // makes sense to flatten the group here
  // also makes sense to make this one large template
  void _recursivelyAddStructMembers(llvm::Type *type);
  void _addMember(size_t size, llvm::Type *typehint);

  public:
  Register *registerAtOffset(off_t offset, size_t size);
  static RegisterMap *registerMapForStateStructure(llvm::StructType *target);
};

}
