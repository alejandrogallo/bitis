#ifndef _BITIS_SRC_
#define _BITIS_SRC_

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <array>
#include <algorithm>

enum BIT { H=1, L=0 };

struct Wire {
  void set(BIT s) { state = s; };
  BIT get() const { return state; };
  private:
  BIT state=L;
};


template <int N>
struct BUS {
  void set(std::array<BIT,N> s) { state = s; };
  std::array<BIT,N> get() const { return state; };
  private:
  std::array<BIT,N> state{L};
};

struct Component {
  std::vector<Wire*> inputs;
  std::vector<Wire*> outputs;
  std::vector<Component*> components;
  virtual ~Component() {
    for (auto component: components) { delete component; }
  }
  virtual void operator()() {
    for (auto &component: components) { (*component)(); }
  };
  virtual void onRise() {
    std::for_each(components.begin(), components.end(),
        [](Component* c) { c->onRise(); });
  };
  virtual void onFall() {
    std::for_each(components.begin(), components.end(),
        [](Component* c) { c->onFall(); });
  };
};

struct SequentialComponent: public Component {
  virtual void onRise() {};
  virtual void onFall() {};
};

struct Clock: public Wire {
  void fall() {
    std::for_each(cs.begin(), cs.end(),
      [](Component* c) { c->onFall(); });
    set(L);
  }
  void rise() {
    std::for_each(cs.begin(), cs.end(),
      [](Component* c) { c->onRise(); });
    set(H);
  }
  void attach(Component *c) { cs.push_back(c); }
  private:
  std::vector<Component*> cs;
};

// gates
struct AndGate: public Component {
  AndGate(Wire *a, Wire *b, Wire *out) { inputs = {a,b}; outputs = {out}; }
  void operator()(){
    BIT a = inputs[0]->get(), b = inputs[1]->get();
    BIT out = (a & b) ? H : L;
    outputs[0]->set(out);
  }
};
struct OrGate: public Component {
  OrGate(Wire *a, Wire *b, Wire *out) { inputs = {a,b}; outputs = {out}; }
  void operator()(){
    BIT a = inputs[0]->get(), b = inputs[1]->get();
    BIT out = (a | b) ? H : L;
    outputs[0]->set(out);
  }
};
struct NotGate: public Component {
  NotGate(Wire *a, Wire *out) { inputs = {a}; outputs = {out}; }
  void operator()(){
    BIT out = (inputs[0]->get() == L) ? H : L;
    outputs[0]->set(out);
  }
};
struct NandGate: public Component {
  NandGate(Wire *a, Wire *b, Wire *out) {
    inputs = {a,b}; outputs = {out};
    Wire *o = new Wire();
    components.push_back(new AndGate(a, b, o));
    components.push_back(new NotGate(o, out));
  }
};
struct NorGate: public Component {
  NorGate(Wire *a, Wire *b, Wire *out) {
    inputs = {a,b}; outputs = {out};
    Wire *o = new Wire();
    components.push_back(new OrGate(a, b, o));
    components.push_back(new NotGate(o, out));
  }
};
struct XorGate: public Component {
  XorGate(Wire *a, Wire *b, Wire *out) {
    inputs = {a,b}; outputs = {out};
    Wire *o1 = new Wire();
    Wire *o2 = new Wire();
    Wire *o3 = new Wire();
    components.push_back(new OrGate(a, b, o1));
    components.push_back(new AndGate(a, b, o2));
    components.push_back(new NotGate(o2, o3));
    components.push_back(new AndGate(o1, o3, out));
  }
};
struct SRLatch: public Component {
  Wire *s, *r, *q, *_q;
  SRLatch(Wire *S, Wire *R, Wire *Q, Wire *_Q) {
    inputs = {S,R}; outputs = {Q, _Q};
    s = S; r = R; q = Q; _q = _Q;
  }
  void operator()() {
    if (s->get() == H && r->get() == H) {
      throw new std::range_error("SRLatch with values S, R = H, H");
    } else if (s->get() == H && r->get() == L) {
      q->set(H); _q->set(L);
    } else if (s->get() == L && r->get() == H) {
      _q->set(H); q->set(L);
    }
  }
};
struct Multiplexer: public Component {
  Wire *a, *b, *sel, *out;
  Multiplexer(Wire *A, Wire *B, Wire *SEL, Wire *OUT) {
    inputs = {A, B, SEL}; outputs = {OUT};
    a = A; b = B; sel = SEL; out = OUT;
  }
  void operator()() {
    if (sel->get() == L) {
      out->set(a->get());
    } else {
      out->set(b->get());
    }
  }
};

struct DataFlipFlop: public Component {
  Wire *in, *out;
  Clock *clk;
  DataFlipFlop(Wire *IN, Wire *OUT, Clock *CLK): in(IN), out(OUT), clk(CLK) {
    clk->attach(this);
  }
  void onRise() { out->set(in->get()); }
};

struct OneBitRegister: public Component {
  Wire *in, *out, *load;
  Clock *clk;
  OneBitRegister(Wire *IN, Wire *OUT, Wire *LOAD, Clock *CLK):
      in(IN), out(OUT), load(LOAD), clk(CLK) {
    clk->attach(this);
    Wire *o = new Wire();
    components.push_back(new Multiplexer(in, out, load, o));
    components.push_back(new DataFlipFlop(o, out, clk));
  }
};

#endif
