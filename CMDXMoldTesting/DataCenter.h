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

	void SetMaxInjectionPressure(double pre)
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

private:
    DataCenter() {m_dDiaScrew=0, m_dMaxInjPre=0;}                   // Constructor? (the {} brackets) are needed here.
    // Dont forget to declare these two. You want to make sure they
    // are unaccessable otherwise you may accidently get copies of
    // your singleton appearing.
    DataCenter(DataCenter const&);              // Don't Implement
    void operator=(DataCenter const&); // Don't implement
	double m_dDiaScrew;
	double m_dMaxInjPre;
	double m_dVolume;
	double m_dColdRunnerVolume;
	int m_iMaterialSel;
	double m_dVolumeExpansion;
	double m_dMaxScrewStroke;
	double m_dGateThickness;
};
