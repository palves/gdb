struct A
{
  int function ();
};

int A::function ()
{
  return 2;
}

int
function ()
{
  return 0;
}

int
function (int i, int b)
{
  return 1;
}

namespace gdb {

int
function ()
{
  return 1;
}

int
function (int i, int b)
{
  return 1;
}

int
function (long l)
{
  return 1;
}

int
ns_function (long l)
{
  return 1;
}

struct A
{
  int function ();
};

int A::function ()
{
  return 2;
}

}

using namespace gdb;

::A some_a;
gdb::A gdb_some_a;

int
main ()
{
  return ::function () + gdb::function () + some_a.function () + gdb_some_a.function ();
}
