//
// StateSTree.cpp
//
// Copyright (c) 2012 -- 2016 Jun Kawahara
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software
// and associated documentation files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
// BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "StateSTree.hpp"

namespace frontier_lib {

using namespace std;

// mate update 後の終端判定。
// 0終端なら 0, 1終端なら 1, どちらでもない場合は -1 を返す。
int StateSTree::CheckTerminalPost(MateSTree* mate)
{
    if (IsLastEdge()) {
        Edge edge = GetCurrentEdge();
        if (mate->frontier[edge.src].comp == mate->frontier[edge.dest].comp) {
            return 1;
        } else {
            return 0;
        }
    } else {
        for (int i = 0; i < frontier_manager_.GetLeavingFrontierSize(); ++i) {
            mate_t v = frontier_manager_.GetLeavingFrontierValue(i); // フロンティアから抜ける頂点
            bool is_exist = false;
            for (int j = 0; j < frontier_manager_.GetNextFrontierSize(); ++j) {
                if (mate->frontier[v].comp == mate->frontier[frontier_manager_.GetNextFrontierValue(j)].comp) {
                    is_exist = true;
                    break;
                }
            }
            if (!is_exist) { // フロンティア上に値 mate_[v] をもつ頂点が存在しない
                return 0;
            }
        }
        return -1;
    }
}

} // the end of the namespace
