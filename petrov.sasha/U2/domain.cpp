#include "domain.hpp"

void petrov::initDataBase(DataBase & db)
{
  detail::initArray(db.persons);
  try
  {
    detail::initArray(db.meetings);
  }
  catch (...)
  {
    detail::destroyArray(db.persons);
    throw;
  }
}

void petrov::destroyDataBase(DataBase & db) noexcept
{
  detail::destroyArray(db.persons);
  detail::destroyArray(db.meetings);
}
