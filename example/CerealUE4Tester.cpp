#include "CerealUE4Tester.h"

AMyPawn::AMyPawn()
{
  PrimaryActorTick.bCanEverTick = true;
}

void AMyPawn::BeginPlay()
{
  Super::BeginPlay();
  
  FString json;
  
  FCerealUE4Test to_json;
  // output to JSON
  {
    to_json.String = TEXT( "Hello, こんにちは." );
    to_json.Name = TEXT( "Tea, чай, តែ." );
    to_json.DateTime = FDateTime::UtcNow();
    to_json.Timespan = FTimespan( 123, 45, 6, 7 );
    to_json.Vector = FVector::UpVector;
    to_json.Vector2D.X = 2;
    to_json.Vector2D.Y = 20;
    to_json.ArrayI32 = { 123, -456, 789 };
    to_json.ArrayBool = { true, false, true, true, false };
    to_json.ArrayString = { TEXT( "hoge" ), TEXT( "fuga" ), TEXT( "piyo" ) };
    to_json.ArrayVector = { { 1,2,3 }, { 4,5,6 }, { 7,8,9 } };
    to_json.SetI32 = { 1, 1, 2, 3, 4, 4 };
    to_json.MapI32I32.Emplace( 1, 1 );
    to_json.MapI32I32.Emplace( 2, 4 );
    to_json.MapI32I32.Emplace( 3, 9 );
    to_json.Box = FBox( FVector( 1,1,1 ), FVector( 2,2,2 ) );
    to_json.Box2D = FBox2D( FVector2D( 1,1 ), FVector2D( 2,2 ) );
    to_json.Sphere = FSphere( FVector( 1,2,3 ), 1.234f );
    to_json.CapsuleShape = FCapsuleShape( FVector( 2,3,4), 3, FVector( 0,1,0 ), 5 );
    to_json.IntVector = FIntVector( -1, -2, -3 );
    to_json.IntPoint = FIntPoint( -4, -5 );
    to_json.IntVector4 = FIntVector4( -4 );
    to_json.UintVector4 = FUintVector4( 1, 2, 3, 4 );
    to_json.IntRect = FIntRect( -1, -2, 1, 2 );
    to_json.Plane = FPlane( 0, 0, 1, 1 );
    to_json.Matrix = FMatrix::Identity;
    to_json.Matrix2x2 = FMatrix2x2();
    to_json.Quat = FQuat( FRotator( 90, 45, 30 ) );
    to_json.Quat2D = FQuat2D( 1.73f );
    to_json.Shear2D = FShear2D( 1, 2 );
    to_json.Scale = FScale( FVector( 1, 2, 3 ) );
    to_json.Scale2D = FScale2D( FVector2D( 4, 5 ) );
    to_json.FloatInterval.Min = 3;
    to_json.FloatInterval.Max = 5;
    to_json.TwoVectors = FTwoVectors( FVector::UpVector, FVector::ForwardVector );
    to_json.OrientedBox.AxisX = FVector::ForwardVector;
    to_json.OrientedBox.AxisY = FVector::RightVector;
    to_json.OrientedBox.AxisZ = FVector::UpVector;
    to_json.OrientedBox.Center = FVector( 1, 2, 3 );
    to_json.OrientedBox.ExtentX = 0.1f;
    to_json.OrientedBox.ExtentY = 0.2f;
    to_json.OrientedBox.ExtentZ = 0.3f;
    to_json.BigInt96.Parse( TEXT( "0x0123456789ABCDEF01234567" ) );
    std::stringstream buffer;
    {
      cereal::JSONOutputArchive a( buffer );
      a( cereal::make_nvp( "FCerealUE4Test", to_json ) );
    }
    json = UTF8_TO_TCHAR( buffer.str().data() );
    UE_LOG( LogTemp, Log, TEXT( "%s" ), *json )
  }
  
  FCerealUE4Test from_json;
  // input from JSON
  {
    std::stringstream buffer;
    buffer << TCHAR_TO_UTF8( *json );
    cereal::JSONInputArchive a( buffer );
    a( from_json );
    
    UE_LOG( LogTemp, Log, TEXT( "String: %s" ), *from_json.String )
    UE_LOG( LogTemp, Log, TEXT( "Name: %s" ), *from_json.Name.ToString() )
    UE_LOG( LogTemp, Log, TEXT( "DateTime: %s" ), *from_json.DateTime.ToIso8601() )
    UE_LOG( LogTemp, Log, TEXT( "Timespan: %s" ), *from_json.Timespan.ToString() )
    UE_LOG( LogTemp, Log, TEXT( "Vector: %s" ), *from_json.Vector.ToString() )
    UE_LOG( LogTemp, Log, TEXT( "Vector2D: %s" ), *from_json.Vector2D.ToString() )
    for ( int32 i = 0; i < from_json.ArrayI32.Num(); ++i )
      UE_LOG( LogTemp, Log, TEXT( "ArrayI32[%d]: %d" ), i, from_json.ArrayI32[ i ] )
    for ( int32 i = 0; i < from_json.ArrayBool.Num(); ++i )
      UE_LOG( LogTemp, Log, TEXT( "ArrayBool[%d]: %s" ), i, from_json.ArrayBool[ i ] ? TEXT( "true" ) : TEXT( "false" ) )
    for ( int32 i = 0; i < from_json.ArrayString.Num(); ++i )
      UE_LOG( LogTemp, Log, TEXT( "ArrayString[%d]: %s" ), i, *from_json.ArrayString[ i ] )
    for ( int32 i = 0; i < from_json.ArrayVector.Num(); ++i )
      UE_LOG( LogTemp, Log, TEXT( "ArrayVector[%d]: %s" ), i, *from_json.ArrayVector[ i ].ToString() )
    {
      int32 i = 0;
      for ( const auto& e : from_json.SetI32 )
        UE_LOG( LogTemp, Log, TEXT( "SetI32[%d]: %d" ), i++, e )
    }
    for ( const auto& p : from_json.MapI32I32 )
      UE_LOG( LogTemp, Log, TEXT( "MapI32I32[%d]: %d" ), p.Key, p.Value )
    UE_LOG( LogTemp, Log, TEXT( "Box: %s" ), *from_json.Box.ToString() )
    UE_LOG( LogTemp, Log, TEXT( "Box2D: %s" ), *from_json.Box2D.ToString() )
    UE_LOG( LogTemp, Log, TEXT( "Sphere: Center={%s} W={%f}" ), *from_json.Sphere.Center.ToString(), from_json.Sphere.W )
    UE_LOG( LogTemp, Log, TEXT( "CapsuleShape: Center={%s} Radius={%f} Orientation={%s} Length={%f}" ), *from_json.CapsuleShape.Center.ToString(), from_json.CapsuleShape.Radius, *from_json.CapsuleShape.Orientation.ToString(), from_json.CapsuleShape.Length )
    UE_LOG( LogTemp, Log, TEXT( "IntVector: (X=%d Y=%d Z=%d)" ), from_json.IntVector.X, from_json.IntVector.Y, from_json.IntVector.Z )
    UE_LOG( LogTemp, Log, TEXT( "IntPoint: (X=%d Y=%d)" ), from_json.IntPoint.X, from_json.IntPoint.Y )
    UE_LOG( LogTemp, Log, TEXT( "IntVector4: (X=%d Y=%d Z=%d W=%d)" ), from_json.IntVector4.X, from_json.IntVector4.Y, from_json.IntVector4.Z, from_json.IntVector4.W )
    UE_LOG( LogTemp, Log, TEXT( "UintVector4: (X=%d Y=%d Z=%d W=%d)" ), from_json.UintVector4.X, from_json.UintVector4.Y, from_json.UintVector4.Z, from_json.UintVector4.Z )
    UE_LOG( LogTemp, Log, TEXT( "IntRect: Min={(X=%d Y=%d)} Max={(X=%d Y=%d)}" ), from_json.IntRect.Min.X, from_json.IntRect.Min.Y, from_json.IntRect.Max.X, from_json.IntRect.Max.Y )
    UE_LOG( LogTemp, Log, TEXT( "Plane: (X=%f Y=%f Z=%f W=%f)" ), from_json.Plane.X, from_json.Plane.Y, from_json.Plane.Z, from_json.Plane.W )
    UE_LOG( LogTemp, Log, TEXT( "Matrix: %s" ), *from_json.Matrix.ToString() )
    {
      float m00 = 0, m01 = 0, m10 = 0, m11 = 0;
      from_json.Matrix2x2.GetMatrix( m00, m01, m10, m11 );
      UE_LOG( LogTemp, Log, TEXT( "Matrix: [%f %f] [%f %f]" ), m00, m01, m10, m11 )
    }
    UE_LOG( LogTemp, Log, TEXT( "Quat: (X=%f Y=%f Z=%f W=%f)" ), from_json.Quat.X, from_json.Quat.Y, from_json.Quat.Z, from_json.Quat.W )
    {
      const auto buffer = from_json.Quat2D.GetVector();
      UE_LOG( LogTemp, Log, TEXT( "Quat2D: (X=%f Y=%f)" ), buffer.X, buffer.Y )
    }
    {
      const auto buffer = from_json.Shear2D.GetVector();
      UE_LOG( LogTemp, Log, TEXT( "Shear2D: (X=%f Y=%f)" ), buffer.X, buffer.Y )
    }
    {
      const auto buffer = from_json.Scale.GetVector();
      UE_LOG( LogTemp, Log, TEXT( "Scale: (X=%f Y=%f Z=%f)" ), buffer.X, buffer.Y, buffer.Z )
    }
    {
      const auto buffer = from_json.Scale2D.GetVector();
      UE_LOG( LogTemp, Log, TEXT( "Scale2D: (X=%f Y=%f)" ), buffer.X, buffer.Y )
    }
    UE_LOG( LogTemp, Log, TEXT( "FloatInterval: Min=%f Max=%f" ), from_json.FloatInterval.Min, from_json.FloatInterval.Max )
    UE_LOG( LogTemp, Log, TEXT( "TwoVectors: %s" ), *from_json.TwoVectors.ToString() )
    UE_LOG( LogTemp, Log, TEXT( "OrientedBox: AxisX={%s} AxisY={%s} AxisZ={%s} Center={%s} ExtentY={%f} ExtentZ={%f}" ), *from_json.OrientedBox.AxisX.ToString(), *from_json.OrientedBox.AxisY.ToString(), *from_json.OrientedBox.AxisZ.ToString(), *from_json.OrientedBox.Center.ToString(), from_json.OrientedBox.ExtentX, from_json.OrientedBox.ExtentY, from_json.OrientedBox.ExtentZ )
    UE_LOG( LogTemp, Log, TEXT( "BigInt96: %s" ), *from_json.BigInt96.ToString() );
  }
  
  {
    const auto r = to_json == from_json;
    UE_LOG( LogTemp, Log, TEXT( "( to_json == from_json ): %s" ), r ? TEXT( "true" ) : TEXT( "false" ) )
    if ( ! r )
    {
      UE_LOG( LogTemp, Fatal, TEXT( "FCerealUE4Test was failed." ) )
    }
  }
}
