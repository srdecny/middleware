import java.io.Serializable;

public class SaleConfirmation implements Serializable {
    private static final long serialVersionUID = 0xF00DBABE;

    public boolean confirmed;
	public String goodsName;

	public SaleConfirmation(boolean confirmed, String goodsName) {
        this.confirmed = confirmed;
		this.goodsName = goodsName;
	}
}