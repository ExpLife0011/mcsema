// DeadStoreEliminator.cpp
//

#include <cstdint>
#include <list>
#include <vector>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/Support/raw_ostream.h>

#include "mcsema/BC/DeadStoreEliminator.h" 

namespace mcsema {

char mcsema::DeadStoreEliminationPass::ID = 0;

DeadStoreEliminationPass::~DeadStoreEliminationPass() {
	delete rMap;
}

bool DeadStoreEliminationPass::runOnBasicBlock(BasicBlock &bb) {
	errs() << "[Begin Dead Store Elim on BB]\n";

	for (auto iter = bb.begin(); iter != bb.end(); iter++) {
		Instruction *inst = &*iter;
		
		// get all operations that are pointers
		// if they reference state structure
		// let's determine the register
		if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(inst)) {
			// should maybe also check regular instructions
			// for ops that may reference this?
			for (unsigned int i = 0; i < gep->getNumOperands(); i++) {
				errs() << "Operand " << i << ": " << gep->getOperand(i)->getValueName() << "\n";
			}
			errs() << *inst << "\n";
		}

		//for (unsigned int i = 0; i < inst->getNumOperands(); i++) {
		//	Value *vp = inst->getOperand(i);
		//	if (vp->getType()->isPointerTy()) {
		//		// check if references state structure
		//		// if so, let's move forward 
		//		//errs() << "[" << vp->getName() << "]\n";
		//		break;
		//	}
		//}
	}

	errs() << "[End Dead Store Elim on BB]\n";

	return false;
}

}
