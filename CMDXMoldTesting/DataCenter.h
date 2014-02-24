#pragma once
class DataCenter
{
public:
	static DataCenter& getInstance()
    {
        static DataCenter instance; // Guaranteed to be destroyed.
                                // Instantiated on first use.
        return instance;
    }

	void SetDiaScrew(double dia)
    {
		m_dDiaScrew = dia;
    }
	double GetDiaScrew()
    {
        return m_dDiaScrew;
    }

	void SetMaxInjectionPressure(double pre) // = machine pressure
    {
		m_dMaxInjPre = pre;
    }
	double GetMaxInjectionPressure()
    {
		return m_dMaxInjPre;
    }

	void SetPartVolume(double v)
	{
		m_dVolume = v;
	}
	double GetPartVolume()
	{
		return m_dVolume;
	}

	void SetColdRunnerVolume(double crv)
	{
		m_dColdRunnerVolume = crv;

		//TRACE("%lf", m_dColdRunnerVolume);
	}
	double GetColdRunnerVolume()
	{
		return m_dColdRunnerVolume;
	}

	void SetHotRunnerVolume(double hrv)
	{
		m_dHotRunnerVolume = hrv;

		//TRACE("%lf", m_dColdRunnerVolume);
	}
	double GetHotRunnerVolume()
	{
		return m_dHotRunnerVolume;
	}

	void SetMaterialSel(int material)
	{
		m_iMaterialSel = material;
	}
	double GetMaterialSel()
	{
		return m_iMaterialSel;
	}

	void SetMaxScrewStroke(int stroke)
	{
		m_dMaxScrewStroke = stroke;
	}
	double GetMaxScrewStroke()
	{
		return m_dMaxScrewStroke;
	}

	void SetGateThickness(double gt)
	{
		m_dGateThickness = gt;
	}
	double GetGateThickness()
	{
		return m_dGateThickness;
	}

	void SetMaxPartThickness(double mpt)
	{
		m_dMaxPartThickness = mpt;
	}
	double GetMaxPartThickness()
	{
		return m_dMaxPartThickness;
	}

private:
    DataCenter() {m_dDiaScrew=0, m_dMaxInjPre=0, m_dMaxScrewStroke=0, 
		m_dVolume=0, m_dColdRunnerVolume=0, m_dHotRunnerVolume=0, m_dGateThickness=0, m_dMaxPartThickness=0,
		m_iMaterialSel=0;}                   // Constructor? (the {} brackets) are needed here.
    // Dont forget to declare these two. You want to make sure they
    // are unaccessable otherwise you may accidently get copies of
    // your singleton appearing.
    DataCenter(DataCenter const&);              // Don't Implement
    void operator=(DataCenter const&); // Don't implement
	double m_dDiaScrew;
	double m_dMaxInjPre;
	double m_dVolume;
	double m_dColdRunnerVolume;
	double m_dHotRunnerVolume;
	int m_iMaterialSel;
	double m_dMaxScrewStroke;
	double m_dGateThickness;
	double m_dMaxPartThickness;
};
