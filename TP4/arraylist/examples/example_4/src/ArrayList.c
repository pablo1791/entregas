#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/ArrayList.h"

// funciones privadas
int resizeUp(ArrayList* this);
int expand(ArrayList* this,int index);
int contract(ArrayList* this,int index);

#define AL_INCREMENT      10
#define AL_INITIAL_VALUE  10
//___________________

/** \brief Allocate a new arrayList with AL_INITIAL_VALUE elements.
 * \param void
 * \return ArrayList* Return (NULL) if Error [if can't allocate memory]
 *                  - (pointer to new arrayList) if ok
 */
ArrayList* al_newArrayList(void)
{
    ArrayList* this;
    ArrayList* returnAux = NULL;
    void* pElements;
    this = (ArrayList *)malloc(sizeof(ArrayList));

    if(this != NULL)
    {
        pElements = malloc(sizeof(void *)*AL_INITIAL_VALUE );
        if(pElements != NULL)
        {
            this->size=0;
            this->pElements=pElements;
            this->reservedSize=AL_INITIAL_VALUE;
            this->add=al_add;
            this->len=al_len;
            this->set=al_set;
            this->remove=al_remove;
            this->clear=al_clear;
            this->clone=al_clone;
            this->get=al_get;
            this->contains=al_contains;
            this->push=al_push;
            this->indexOf=al_indexOf;
            this->isEmpty=al_isEmpty;
            this->pop=al_pop;
            this->subList=al_subList;
            this->containsAll=al_containsAll;
            this->deleteArrayList = al_deleteArrayList;
            this->sort = al_sort;
            returnAux = this;
        }
        else
        {
            free(this);
        }
    }
    return returnAux;
}


/** \brief  Add an element to arrayList and if is
 *          nessesary resize the array
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (0) if Ok
 *
 */
int al_add(ArrayList* this, void* pElement) //Agrega un elemento al final de ArrayList.
{
    int returnAux = -1;
    if(this != NULL &&  pElement != NULL)
    {
        returnAux=0;
        *((this->pElements) + (this->size)) = pElement;
        this->size++;
        if(this->size == this->reservedSize)
        {
            resizeUp(this);
            if( resizeUp(this) == -1)
            {
                returnAux=-1;
            }
        }
    }

    return returnAux;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Ok
 *
 */
int al_deleteArrayList(ArrayList* this) //Elimina el ArrayList.
{
    int returnAux = -1;
    if(this != NULL)
    {
        free(this->pElements);
        free(this);
        returnAux=0;
    }

    return returnAux;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return length of array or (-1) if Error [pList is NULL pointer]
 *
 */
int al_len(ArrayList* this)  //Retorna el tama�o del ArrayList.
{
    int returnAux = -1;
    if(this != NULL)
    {
        returnAux=this->size;
    }

    return returnAux;
}


/** \brief  Get an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return void* Return (NULL) if Error [pList is NULL pointer or invalid index] - (Pointer to element) if Ok
 *
 */
void* al_get(ArrayList* this, int index)   // Retorna un puntero al elemento que se encuentra en el �ndice especificado
{
    void* returnAux = NULL;

    if(this != NULL && index >= 0 && index <= this->size)
    {
        returnAux = *(this->pElements + index);
    }
    return returnAux;
}


/** \brief  Find if pList contains at least one element pElement
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer]
 *                  - ( 0) if Ok but not found a element
 *                  - ( 1) if this list contains at least one element pElement
 *
 */
int al_contains(ArrayList* this, void* pElement)  //Comprueba si existe el elemento que se le pasa como par�metro
{
    int returnAux = -1;
    int i;
    if(this != NULL && pElement != NULL)
    {
        for(i=0; i < this->size; i++)
        {
            if(pElement == al_get(this, i))
            {
                returnAux=1;
                break;
            }
            returnAux=0;
        }
    }
    return returnAux;
}


/** \brief  Set a element in pList at index position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 *
 */
int al_set(ArrayList* this, int index,void* pElement) //Inserta un elemento en el ArrayList, en el �ndice especificado.
{
    int returnAux = -1;
    if(this != NULL && pElement != NULL && index >= 0 && index <= this->size)
    {
        *(this->pElements + index) = pElement;
        returnAux = 0;
    }
    return returnAux;
}


/** \brief  Remove an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_remove(ArrayList* this,int index)  //Elimina un elemento del ArrayList, en el �ndice especificado
{
    int returnAux = -1;

    if(this != NULL && index >= 0 && index < this->size)
    {
        contract(this, index);
        returnAux=0;
    }
    return returnAux;
}



/** \brief Removes all of the elements from this list
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer]
 *                  - ( 0) if Ok
 */
int al_clear(ArrayList* this) //Borra todos los elementos de ArrayList.
{
    int returnAux = -1;
    if(this != NULL)
    {
        free(this->pElements);
        this->size=0;
        returnAux=0;
    }
    return returnAux;
}



/** \brief Returns an array containing all of the elements in this list in proper sequence
 * \param pList ArrayList* Pointer to arrayList
 * \return ArrayList* Return  (NULL) if Error [pList is NULL pointer]
 *                          - (New array) if Ok
 */
ArrayList* al_clone(ArrayList* this) //Retorna un nuevo ArrayList copia del ArrayList original.
{
    ArrayList* returnAux = NULL;
    if(this != NULL)
    {
        returnAux=this;
    }
    return returnAux;
}




/** \brief Inserts the element at the specified position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_push(ArrayList* this, int index, void* pElement) //Desplaza los elementos e inserta en la posici�n index.
{
    int returnAux = -1;

    if(this != NULL && pElement != NULL && index >= 0 && index <= this->size)
    {
        expand(this, index);
        al_set(this, index, pElement);
        returnAux=0;
    }
    return returnAux;
}



/** \brief Returns the index of the first occurrence of the specified element
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (index to element) if Ok
 */
int al_indexOf(ArrayList* this, void* pElement) //Retorna el �ndice de la primera aparici�n de un elemento (element) en el ArrayList
{
    int returnAux = -1;
    int i;
    if(this != NULL && pElement != NULL)
    {
        for(i=0; i<this->size; i++)
        {
            if(al_get(this, i) == pElement)
            {
                returnAux=i;
                break;
            }
        }
    }

    return returnAux;
}



/** \brief Returns true if this list contains no elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Not Empty - (1) if is Empty
 */
int al_isEmpty(ArrayList* this) //Retorna cero si contiene elementos y uno si no los tiene.
{
    int returnAux = -1;
    if(this != NULL)
    {
        returnAux=0;
        if(al_len(this) == 0)
        {
            returnAux=1;
        }
    }
    return returnAux;
}




/** \brief Remove the item at the given position in the list, and return it.
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid index]
 *                  - ( element pointer) if Ok
 */
void* al_pop(ArrayList* this,int index) //Retorna un puntero al elemento que se encuentra
//en el �ndice especificado y luego lo elimina de la lista.
{
    void* returnAux = NULL;

    if(this != NULL && index >= 0 && index <= this->size)
    {
        returnAux=al_get(this, index);
        al_remove(this, index);
    }
    return returnAux;
}


/** \brief Returns a new arrayList with a portion of pList between the specified
 *         fromIndex, inclusive, and toIndex, exclusive.
 * \param pList ArrayList* Pointer to arrayList
 * \param from int Initial index of the element (inclusive)
 * \param to int Final index of the element (exclusive)
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid 'from' or invalid 'to']
 *                  - ( pointer to new array) if Ok
 */
ArrayList* al_subList(ArrayList* this,int from,int to) //Retorna un nuevo ArrayList con el subconjunto de elementos
{
    ArrayList* returnAux = NULL;

    if(this != NULL && from >= 0 && from <= al_len(this) && to >= 0 && to <= al_len(this) && from <= to)
    {
        ArrayList* nuevaLista = al_newArrayList();

        for(from=0; from < to; from++)
        {
            al_add(nuevaLista, al_get(this, from));
        }
        if(nuevaLista!= NULL)
        {
            returnAux=nuevaLista;
        }
    }
    return returnAux ;
}





/** \brief Returns true if pList list contains all of the elements of pList2
 * \param pList ArrayList* Pointer to arrayList
 * \param pList2 ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList or pList2 are NULL pointer]
 *                  - (0) if Not contains All - (1) if is contains All
 */
int al_containsAll(ArrayList* this,ArrayList* this2) //Comprueba si los elementos pasados son contenidos por el ArrayList
{
    int returnAux = -1;
    int i;
    if(this != NULL && this2 != NULL)
    {
        returnAux=1;
        for(i=0; i<=al_len(this2); i++)
        {
            if(al_contains(this, al_get(this2,i))==0)
            {
                returnAux=0;
            }
            break;
        }
    }
    return returnAux;
}

/** \brief Sorts objects of list, use compare pFunc
 * \param pList ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [pList or pFunc are NULL pointer]
 *                  - (0) if ok
 */
int al_sort(ArrayList* this, int (*pFunc)(void*,void*), int order) // Ordena los elementos del array
{
    int returnAux = -1;



    return returnAux;
}


/** \brief Increment the number of elements in pList in AL_INCREMENT elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
int resizeUp(ArrayList* this)
{
    int returnAux = -1;
    void* auxiliar;

    if(this != NULL)
    {
        auxiliar=realloc(this->pElements, sizeof(void*) * (this->reservedSize + AL_INCREMENT));
        if(auxiliar != NULL)
        {
            this->pElements=auxiliar;
            this->reservedSize = this->reservedSize + AL_INCREMENT;
            returnAux = 0;
        }
    }

    return returnAux;

}

/** \brief  Expand an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int expand(ArrayList* this,int index)
{
    int returnAux = -1;
    int i;

    if(this != NULL && index >= 0 && index <= this->size)
    {
        returnAux=0;
        this->size++;
        for(i=this->size; i > index; i--)
        {
            al_set(this, i, al_get(this, i-1));
        }
    }

    return returnAux;
}

/** \brief  Contract an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int contract(ArrayList* this,int index)
{
    int returnAux = -1;
    int i;
    for(i=index; i < this->size; i++)
    {
        if(this != NULL && index >= 0 && index < this->size)
        {
            al_set(this, i, al_get(this, i+1));
        }
        returnAux=0;
    }
    this->size--;
    return returnAux;
}