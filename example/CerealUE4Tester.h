#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#pragma warning(push)
#pragma warning(disable:4668)
#include "cereal/cereal.hpp"
#include "cereal/archives/json.hpp"
#pragma warning(pop)

#include "cereal-UE4.hxx"

#include "CerealUE4Tester.generated.h"

USTRUCT( BlueprintType ) 
struct FCerealUE4Test
{ GENERATED_BODY()
  UPROPERTY( BlueprintReadWrite ) FString String;
  UPROPERTY( BlueprintReadWrite ) FName Name;
  UPROPERTY( BlueprintReadWrite ) FDateTime DateTime;
  UPROPERTY( BlueprintReadWrite ) FTimespan Timespan;
  UPROPERTY( BlueprintReadWrite ) FVector Vector;
  UPROPERTY( BlueprintReadWrite ) FVector Vector2D;
  UPROPERTY( BlueprintReadWrite ) TArray< int32 > ArrayI32;
  UPROPERTY( BlueprintReadWrite ) TArray< bool > ArrayBool;
  UPROPERTY( BlueprintReadWrite ) TArray< FString > ArrayString;
  UPROPERTY( BlueprintReadWrite ) TArray< FVector > ArrayVector;
  UPROPERTY( BlueprintReadWrite ) TSet< int32 > SetI32;
  UPROPERTY( BlueprintReadWrite ) TMap< int32, int32 > MapI32I32;
  UPROPERTY( BlueprintReadWrite ) FBox Box;
  UPROPERTY( BlueprintReadWrite ) FBox2D Box2D;
  FSphere Sphere;
  FCapsuleShape CapsuleShape;
  FIntVector IntVector;
  FIntPoint IntPoint;
  FIntVector4 IntVector4;
  FUintVector4 UintVector4;
  FIntRect IntRect;
  FPlane Plane;
  FMatrix Matrix;
  FMatrix2x2 Matrix2x2;
  FQuat Quat;
  FQuat2D Quat2D;
  FShear2D Shear2D;
  FScale Scale;
  FScale2D Scale2D;
  FFloatInterval FloatInterval;
  FTwoVectors TwoVectors;
  FOrientedBox OrientedBox;
  TBigInt< 96 > BigInt96; 
  
  bool operator==( const FCerealUE4Test& t )
  {
    if ( SetI32.Num() != t.SetI32.Num() )
      return false;
    for ( const auto& e : SetI32 )
      if ( ! t.SetI32.Contains( e ) )
        return false;
    
    if ( MapI32I32.Num() != t.MapI32I32.Num() )
      return false;
    {
      TArray< int32 > keys;
      MapI32I32.GenerateKeyArray( keys );
      for ( const auto& key : keys )
      {
        const auto pa = MapI32I32.Find( key );
        const auto pb = t.MapI32I32.Find( key );
        if ( pb == nullptr || *pa != *pb )
          return false;
      }
    }
    
    if ( String != t.String )
      return false;
    if ( Name != t.Name )
      return false;
    if ( DateTime.ToIso8601() != t.DateTime.ToIso8601() )
      return false;
    if ( Timespan.ToString() != t.Timespan.ToString() )
      return false;
    if ( Vector != t.Vector )
      return false;
    if ( Vector2D != t.Vector2D )
      return false;
    if ( ArrayI32 != t.ArrayI32 )
      return false;
    if ( ArrayBool != t.ArrayBool )
      return false;
    if ( ArrayString != t.ArrayString )
      return false;
    if ( ArrayVector != t.ArrayVector )
      return false;
    if ( ! ( Box == t.Box ) )
      return false;
    if ( ! (Box2D == t.Box2D ) )
      return false;
    if ( Sphere.Center != t.Sphere.Center )
      return false;
    if ( Sphere.W != t.Sphere.W )
      return false;
    if ( CapsuleShape.Center != t.CapsuleShape.Center )
      return false;
    if ( CapsuleShape.Radius != t.CapsuleShape.Radius )
      return false;
    if ( CapsuleShape.Orientation != t.CapsuleShape.Orientation )
      return false;
    if ( CapsuleShape.Length != t.CapsuleShape.Length )
      return false;
    if ( IntVector != t.IntVector )
      return false;
    if ( IntPoint != t.IntPoint )
      return false;
    if ( IntVector4 != t.IntVector4 )
      return false;
    if ( UintVector4 != t.UintVector4 )
      return false;
    if ( IntRect != t.IntRect )
      return false;
    if ( Plane != t.Plane )
      return false;
    if ( Matrix != t.Matrix )
      return false;
    if ( Matrix2x2 != t.Matrix2x2 )
      return false;
    if ( Quat != t.Quat )
      return false;
    if ( Quat2D != t.Quat2D )
      return false;
    if ( Shear2D != t.Shear2D )
      return false;
    if ( Scale.GetVector() != t.Scale.GetVector() )
      return false;
    if ( Scale2D != t.Scale2D )
      return false;
    if ( FloatInterval.Min != t.FloatInterval.Min )
      return false;
    if ( FloatInterval.Max != t.FloatInterval.Max )
      return false;
    if ( TwoVectors != t.TwoVectors )
      return false;
    if ( OrientedBox.AxisX != t.OrientedBox.AxisX )
      return false;
    if ( OrientedBox.AxisY != t.OrientedBox.AxisY )
      return false;
    if ( OrientedBox.AxisZ != t.OrientedBox.AxisZ )
      return false;
    if ( OrientedBox.Center != t.OrientedBox.Center )
      return false;
    if ( OrientedBox.ExtentX != t.OrientedBox.ExtentX )
      return false;
    if ( OrientedBox.ExtentY != t.OrientedBox.ExtentY )
      return false;
    if ( OrientedBox.ExtentZ != t.OrientedBox.ExtentZ )
      return false;
    if ( BigInt96 != t.BigInt96 )
      return false;
    return true;
  }
};

template < typename A >
void serialize( A& a, FCerealUE4Test& in )
{
  a
  ( cereal::make_nvp( "String", in.String )
  , cereal::make_nvp( "Name", in.Name )
  , cereal::make_nvp( "DateTime", in.DateTime )
  , cereal::make_nvp( "Timespan", in.Timespan )
  , cereal::make_nvp( "Vector", in.Vector )
  , cereal::make_nvp( "Vector2D", in.Vector2D )
  , cereal::make_nvp( "ArrayI32", in.ArrayI32 )
  , cereal::make_nvp( "ArrayBool", in.ArrayBool )
  , cereal::make_nvp( "ArrayString", in.ArrayString )
  , cereal::make_nvp( "ArrayVector", in.ArrayVector )
  , cereal::make_nvp( "SetI32", in.SetI32 )
  , cereal::make_nvp( "MapI32I32", in.MapI32I32 )
  , cereal::make_nvp( "Box", in.Box )
  , cereal::make_nvp( "Box2D", in.Box2D )
  , cereal::make_nvp( "Sphere", in.Sphere )
  , cereal::make_nvp( "CapsuleShape", in.CapsuleShape )
  , cereal::make_nvp( "IntVector", in.IntVector )
  , cereal::make_nvp( "IntPoint", in.IntPoint )
  , cereal::make_nvp( "IntVector4", in.IntVector4 )
  , cereal::make_nvp( "UintVector4", in.UintVector4 )
  , cereal::make_nvp( "IntRect", in.IntRect )
  , cereal::make_nvp( "Plane", in.Plane )
  , cereal::make_nvp( "Matrix", in.Matrix )
  , cereal::make_nvp( "Matrix2x2", in.Matrix2x2 )
  , cereal::make_nvp( "Quat", in.Quat )
  , cereal::make_nvp( "Quat2D", in.Quat2D )
  , cereal::make_nvp( "Shear2D", in.Shear2D )
  , cereal::make_nvp( "Scale", in.Scale )
  , cereal::make_nvp( "Scale2D", in.Scale2D )
  , cereal::make_nvp( "FloatInterval", in.FloatInterval )
  , cereal::make_nvp( "TwoVectors", in.TwoVectors )
  , cereal::make_nvp( "OrientedBox", in.OrientedBox )
  , cereal::make_nvp( "BigInt96", in.BigInt96 )
  );
}

UCLASS()
class ACerealUE4Tester : public APawn
{ GENERATED_BODY()
public:
  AMyPawn();
protected:
  virtual void BeginPlay() override;
};
