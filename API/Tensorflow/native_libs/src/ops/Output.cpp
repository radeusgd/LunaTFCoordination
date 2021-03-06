#include "Output.h"
#include "../graph/GraphSession.h"

Output::Output(std::shared_ptr<Node> binder, size_t index) : binder(std::move(binder)) {
    hash = std::hash<int>()(index);
    hash = hash_combine(hash, this->binder->hashcode());
}

TF_Output Output::add_to_graph(GraphSession& graph) const {
    if (!graph.exists(this)) {
        binder->add_to_graph(graph);
    }

    return graph.get_output(this);
};

size_t Output::hashcode() const {
    return hash;
}

std::shared_ptr<Tensor> Output::eval() const {
    GraphSession graph;
    graph.add_fetched_output(graph.add_output(this));

    auto res = graph.eval();
    if (res->outputs.empty()) {
        throw std::runtime_error("Internal error: Evaluation yielded no results");
    }
    return res->outputs[0];
}

std::shared_ptr<Node> Output::get_binder() {
    return binder;
}

Output::~Output()
{
    LOG("finalizing ~", binder->hash_log());
}
