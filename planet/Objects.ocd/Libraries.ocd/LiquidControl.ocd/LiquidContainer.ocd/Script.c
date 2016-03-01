/**
 * Liquid Container
 *
 * Basic interface for anything that can contain liquids.
 *
 * Author: Ringwaul, ST-DDT, Marky
 */


func IsLiquidContainer() { return true;}

func GetLiquidContainerMaxFillLevel()
{
	return 0;
}

func IsLiquidContainerForMaterial(string liquid_name)
{
	return true;
}

func GetLiquidAmount(string liquid_name)
{
	var amount = 0;
	for (var liquid in GetLiquidContents())
	if (liquid_name == nil || liquid->GetLiquidType() == liquid_name)
	{
		amount += liquid->~GetLiquidAmount();
	}
	return amount;
}

func GetLiquidContents()
{
	return FindObjects(Find_Container(this), Find_Func("IsLiquid"));
}

// -------------- Interaction
//
// Interfaces for interaction with other objects

/**
Extracts liquid from the container.
@param liquid_name: Material to extract; Wildcardsupport
               Defaults to the current liquid if 'nil' is passed.
@param amount: Max Amount of liquid being extracted;
               Defaults to all contained liquid if 'nil' is passed.
@param destination: Object that extracts the liquid
@return [returned_liquid, returned_amount]
	   - returned_liquid: Material being extracted
	   - returned_amount: Amount being extracted
*/
func RemoveLiquid(string liquid_name, int amount, object destination)
{
	if (amount < 0)
	{
		FatalError(Format("You can remove positive amounts of liquid only, got %d", amount));
	}
	
	var removed = 0;
	for (var liquid in GetLiquidContents())
	{
		if (removed >= amount) break;
	
		if (!liquid_name) liquid_name = liquid->GetLiquidType();
		
		//if (liquid->GetLiquidType() == liquid_name)
		//{
			removed += liquid->RemoveLiquid(liquid_name, amount - removed, destination)[1];
		//}
	}

	return [liquid_name, removed];
}


/** 
Inserts liquid into the container.
@param liquid_name: Material to insert
@param amount: Max Amount of Material being inserted 
@param source: Object which inserts the liquid
@return returned_amount: The inserted amount
*/
func PutLiquid(string liquid_name, int amount, object source)
{
	if (amount < 0)
	{
		FatalError(Format("You can insert positive amounts of liquid only, got %d", amount));
	}
	
	var before = GetLiquidAmount(liquid_name);
	var type = Library_Liquid->GetLiquidID(liquid_name);
	CreateContents(type, amount);
	var after = GetLiquidAmount(liquid_name);
	return after - before;
}
