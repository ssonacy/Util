#ifndef _VALUE_ENCODE_H_
#define _VALUE_ENCODE_H_

class encode_base
{	
protected:

	encode_base( double raw_max , double raw_min , double high , double low );
	virtual ~encode_base() {}

protected:

	inline double get_one_range() const { return one_range_;  }
	inline double get_from_zero() const { return from_zero_;  }

	inline double get_raw_max() const { return raw_max_;  }
	inline double get_raw_min() const { return raw_min_;  }

private:

	double one_range_;
	double from_zero_;

	double raw_max_;
	double raw_min_;
};

// 아날로그 값을 장치마다 정해진 range에 맞게 변환해 주는 클래스
class encoder : private encode_base
{
public:

	encoder( double raw_max , double raw_min , double high , double low );
	virtual ~encoder();

	double encode( double raw ) const;
};

#endif // _VALUE_ENCODE_H_